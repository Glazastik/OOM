package se.chalmers.oomproject.oom;

import android.os.Bundle;
import android.support.v4.app.FragmentManager;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Created by Glazastik on 29/04/15.
 */
public class PersonEditFragment extends android.support.v4.app.Fragment {
    private static DataSingleton data;
    private static Person person;
    private ListView lv;
    List<Map<String, String>> listData;

    public static PersonEditFragment newInstance(Person p) {
        data = DataSingleton.getInstance();
        person = p;
        return new PersonEditFragment();
    }

    public PersonEditFragment() {

    }

    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        View v = inflater.inflate(R.layout.fragment_editperson, container, false);
        TextView editName = (TextView) v.findViewById(R.id.edit_person_name);
        lv = (ListView) v.findViewById(R.id.edit_account_list);
        Button addButton = (Button) v.findViewById(R.id.edit_add_button);

        editName.setText(person.getName());

        listData = new ArrayList<Map<String, String>>();
        for (Account a : person.getAccounts()) {
            Map<String, String> datum = new HashMap<String, String>(2);
            datum.put("name", a.getServiceName());
            datum.put("address", a.getAddress());
            listData.add(datum);
        }

        ArrayAdapter adapter = new ArrayAdapter(getActivity(), android.R.layout.simple_list_item_2, android.R.id.text1, listData) {
            @Override
            public View getView(int position, View convertView, ViewGroup parent) {
                View view = super.getView(position, convertView, parent);
                TextView text1 = (TextView) view.findViewById(android.R.id.text1);
                TextView text2 = (TextView) view.findViewById(android.R.id.text2);

                text1.setText(listData.get(position).get("name"));
                text2.setText(listData.get(position).get("address"));
                return view;
            }
        };

        lv.setAdapter(adapter);

        lv.setOnItemLongClickListener(new AdapterView.OnItemLongClickListener() {
            @Override
            public boolean onItemLongClick(AdapterView<?> parent, View view, int position, long id) {
                person.getAccounts().remove(position);
                ((SimpleAdapter) lv.getAdapter()).notifyDataSetChanged();
                return true;
            }
        });

        addButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                FragmentManager fm = getActivity().getSupportFragmentManager();
                AccountAddFragment a = AccountAddFragment.newInstance(person);
                a.show(fm, "add_account");
            }
        });

        return v;
    }

    public void update(){
        ((ArrayAdapter) lv.getAdapter()).notifyDataSetChanged();
    }

}
