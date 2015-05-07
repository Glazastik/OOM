package se.chalmers.oomproject.oom;

import android.os.Bundle;
import android.support.v4.app.FragmentManager;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;

/**
 * Created by meddan on 26/03/15.
 */
public class NewPersonFragment extends android.support.v4.app.DialogFragment {
    private static DataSingleton data;

    public static NewPersonFragment newInstance() {
        data = DataSingleton.getInstance();
        return new NewPersonFragment();
    }

    public NewPersonFragment() {
    }

    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        View v = inflater.inflate(R.layout.fragment_newperson, container, false);

        getDialog().setTitle(R.string.landing_button1);

        Button b = (Button) v.findViewById(R.id.createButton);
        b.setOnClickListener(new View.OnClickListener() {
            public void onClick(View b) {
                View v = (View) b.getParent();
                if (((EditText) v.findViewById(R.id.nnBox)).getText().toString().length() != 0) {
                    Person c = new Person(0, ((EditText) v.findViewById(R.id.nnBox)).getText().toString());
                    data.addNewPerson(c, getActivity());
                    dismiss();
                    FragmentManager fragmentManager = getActivity().getSupportFragmentManager();
                    fragmentManager.beginTransaction()
                            .replace(R.id.container, ConversationFragment.newInstance(data.getPersons().indexOf(c)))
                            .commit();
                }
            }
        });

        return v;
    }
}
