package se.chalmers.oomproject.oom;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
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

    public static PersonEditFragment newInstance(Person p){
        data = DataSingleton.getInstance();
        person = p;
        return new PersonEditFragment();
    }

    public PersonEditFragment(){

    }

    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        View v = inflater.inflate(R.layout.fragment_editperson, container, false);
        TextView editName = (TextView) v.findViewById(R.id.edit_person_name);
        ListView lv = (ListView) v.findViewById(R.id.edit_account_list);

        editName.setText(person.getName());


        List<Map<String, String>> data = new ArrayList<Map<String, String>>();
        for (Account a : person.getAccounts()) {
            Map<String, String> datum = new HashMap<String, String>(2);
            datum.put("name", a.getServiceName());
            datum.put("address", a.getAddress());
            data.add(datum);
        }

        SimpleAdapter adapter = new SimpleAdapter(getActivity(), data,
                android.R.layout.simple_list_item_2,
                new String[] {"name", "address"},
                new int[] {android.R.id.text1,
                        android.R.id.text2});


        lv.setAdapter(adapter);

        return v;
    }

}
