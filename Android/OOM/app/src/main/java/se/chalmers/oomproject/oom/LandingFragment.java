package se.chalmers.oomproject.oom;

import android.app.Activity;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.GridView;
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
        ListView log = (ListView) v.findViewById(R.id.list_landing);
        log.setAdapter(new LandingAdapter(this.getActivity(),
                data.getConversations()));
        return v;
    }

    @Override
    public void onAttach(Activity activity) {
        super.onAttach(activity);
        ((MainActivity) activity).onSectionAttached();
    }

}
