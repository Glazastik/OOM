package se.chalmers.oomproject.oom;

import android.os.Bundle;
import android.support.v4.app.DialogFragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

/**
 * Created by Glazastik on 29/04/15.
 */
public class AccountAddFragment extends DialogFragment {

    private static Person person;

    public static AccountAddFragment newInstance(Person p){
        person = p;

        return new AccountAddFragment();
    }

    public AccountAddFragment(){

    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_addaccount, container);
        getDialog().setTitle("Add a new account");


        return view;
    }

}
