package se.chalmers.oomproject.oom;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

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
        editName.setText(person.getName());

        return v;
    }

}
