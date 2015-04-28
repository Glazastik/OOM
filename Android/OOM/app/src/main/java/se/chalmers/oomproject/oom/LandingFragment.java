package se.chalmers.oomproject.oom;

import android.app.Activity;
import android.os.Bundle;
import android.support.v4.app.FragmentManager;
import android.support.v7.app.ActionBar;
import android.support.v7.app.ActionBarActivity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.ListView;


/**
 * Created by Glazastik on 15-03-24.
 */
public class LandingFragment extends android.support.v4.app.Fragment {

    private static DataSingleton data;

    /**
     * Returns a new instance of this fragment for the given conversation.
     */
    public static LandingFragment newInstance() {
        LandingFragment fragment = new LandingFragment();
        data = DataSingleton.getInstance();
        return fragment;
    }

    public LandingFragment() {
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View v = inflater.inflate(R.layout.fragment_landing, container, false);

        //Prepare the adapter for the landing list.
        ListView log = (ListView) v.findViewById(R.id.list_landing);
        log.setAdapter(new LandingAdapter(this.getActivity(),
                data.getConversations()));
        log.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {

                FragmentManager fragmentManager = getActivity().getSupportFragmentManager();
                fragmentManager.beginTransaction()
                        .replace(R.id.container, ConversationFragment.newInstance(position))
                        .commit();


            }
        });
        Button newContact = (Button) v.findViewById(R.id.newContact);
        newContact.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                FragmentManager fragmentManager = getActivity().getSupportFragmentManager();
                fragmentManager.beginTransaction()
                        .replace(R.id.container, NewContactFragment.newInstance()).addToBackStack("landing")
                        .commit();


            }
        });

        getActionBar().setTitle(getString(R.string.app_name));

        return v;
    }

    @Override
    public void onAttach(Activity activity) {
        super.onAttach(activity);
        ((MainActivity) activity).onSectionAttached();
    }

    private ActionBar getActionBar() {
        return ((ActionBarActivity) getActivity()).getSupportActionBar();
    }


}
