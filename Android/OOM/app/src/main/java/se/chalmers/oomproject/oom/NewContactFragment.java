package se.chalmers.oomproject.oom;

import android.os.Bundle;
import android.support.v4.app.FragmentManager;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
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

        return v;
    }
}
