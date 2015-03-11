package se.chalmers.oomproject.oom;

import android.app.Activity;
import android.app.Fragment;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

/**
 * Created by Anton on 2015-03-11.
 */
public class ConversationFragment extends android.support.v4.app.Fragment {

    private static final String CONVERSATION_NUBMER = "conversation_number";
    private static DataSingleton data;

    /**
     * Returns a new instance of this fragment for the given conversation.
     */
    public static ConversationFragment newInstance(int pos) {
        ConversationFragment fragment = new ConversationFragment();
        Bundle args = new Bundle();
        args.putInt(CONVERSATION_NUBMER, pos);
        fragment.setArguments(args);
        data = DataSingleton.getInstance();
        return fragment;
    }

    public ConversationFragment() {
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View rootView = inflater.inflate(R.layout.fragment_main, container, false);
        return rootView;
    }

    @Override
    public void onAttach(Activity activity) {
        super.onAttach(activity);
        int conID = getArguments().getInt(CONVERSATION_NUBMER);
        Conversation con = data.getConversations().get(conID);

        ((MainActivity) activity).onSectionAttached(con);
    }

}
