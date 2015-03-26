package se.chalmers.oomproject.oom;

import android.app.Activity;
import android.os.Bundle;
import android.support.v4.app.FragmentManager;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.GridView;
import android.widget.ListView;
import android.widget.TextView;


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

                String title = ((TextView) view.findViewById(R.id.landing_item_name)).getText().toString();
                ((MainActivity) getActivity()).onSectionAttached(title, true);

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
                        .replace(R.id.container, NewContactFragment.newInstance())
                        .commit();
            }
        });


        return v;
    }

    @Override
    public void onAttach(Activity activity) {
        super.onAttach(activity);
        ((MainActivity) activity).onSectionAttached();
    }

}
