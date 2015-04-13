package se.chalmers.oomproject.oom;

import android.os.Bundle;
import android.support.v4.app.FragmentManager;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;

/**
 * Created by meddan on 26/03/15.
 */
public class NewContactFragment extends android.support.v4.app.Fragment {
    private static DataSingleton data;
    public static NewContactFragment newInstance(){
        data = DataSingleton.getInstance();
        return new NewContactFragment();
    }
    public NewContactFragment(){}
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState){

        View v = inflater.inflate(R.layout.fragment_newcontact, container, false);
        Button b = (Button) v.findViewById(R.id.createButton);
        b.setOnClickListener(new View.OnClickListener() {
            public void onClick(View b) {
                View v = (View) b.getParent();
                if (((EditText) v.findViewById(R.id.lnBox)).getText().toString().length() != 0 ||
                        ((EditText) v.findViewById(R.id.fnBox)).getText().toString().length() != 0 ||
                        ((EditText) v.findViewById(R.id.nnBox)).getText().toString().length() != 0) {
                    Contact c = new Contact();
                    c.setFirstName(((EditText) v.findViewById(R.id.fnBox)).getText().toString());
                    c.setLastName(((EditText) v.findViewById(R.id.lnBox)).getText().toString());
                    c.setNickName(((EditText) v.findViewById(R.id.nnBox)).getText().toString());
                    data.addNewContact(c, getActivity());
                    FragmentManager fragmentManager = getActivity().getSupportFragmentManager();
                    fragmentManager.beginTransaction()
                            .replace(R.id.container, ConversationFragment.newInstance(data.getContacts().indexOf(c)))
                            .commit();
                }
            }
        });

        return v;
    }
}
