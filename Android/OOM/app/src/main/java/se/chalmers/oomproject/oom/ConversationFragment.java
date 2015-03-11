package se.chalmers.oomproject.oom;

import android.app.Activity;
import android.app.Fragment;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ListView;

/**
 * Created by Anton on 2015-03-11.
 */
public class ConversationFragment extends android.support.v4.app.Fragment {

    private static final String CONVERSATION_NUMBER = "conversation_number";
    private static int conID;
    private static DataSingleton data;

    /**
     * Returns a new instance of this fragment for the given conversation.
     */
    public static ConversationFragment newInstance(int pos) {
        ConversationFragment fragment = new ConversationFragment();
        Bundle args = new Bundle();
        args.putInt(CONVERSATION_NUMBER, pos);
        conID = pos;
        fragment.setArguments(args);
        data = DataSingleton.getInstance();
        return fragment;
    }

    public ConversationFragment() {
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View v = inflater.inflate(R.layout.fragment_main, container, false);

        ListView log = (ListView) v.findViewById(R.id.chatLogView);
        log.setAdapter(new ArrayAdapter<String>(this.getActivity(),
                android.R.layout.simple_list_item_1,
                data.getConversationMessages(conID)));

        return v;
    }

    @Override
    public void onAttach(Activity activity) {
        super.onAttach(activity);
        int conID = getArguments().getInt(CONVERSATION_NUMBER);
        Conversation con = data.getConversations().get(conID);
        ((MainActivity) activity).onSectionAttached(con);
    }

}
