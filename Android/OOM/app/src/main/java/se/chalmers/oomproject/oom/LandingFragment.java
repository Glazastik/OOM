package se.chalmers.oomproject.oom;

import android.app.Activity;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;


/**
 * Created by Glazastik on 15-03-24.
 */
public class LandingFragment extends android.support.v4.app.Fragment {

    private static DataSingleton data;
    /**
     * Returns a new instance of this fragment for the given conversation.
     */
    public static LandingFragment newInstance(int pos) {
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
        return v;
    }

    @Override
    public void onAttach(Activity activity) {
        super.onAttach(activity);
        ((MainActivity) activity).onSectionAttached();
    }


}
