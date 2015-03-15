package se.chalmers.oomproject.oom;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.view.inputmethod.EditorInfo;
import android.view.inputmethod.InputMethodManager;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;

/**
 * Created by Anton on 2015-03-11.
 */
public class ConversationFragment extends android.support.v4.app.Fragment {

    private static final String CONVERSATION_NUMBER = "conversation_number";
    private static int conID;
    private static DataSingleton data;
    private static Conversation conversation;


    private ListView log;
    private EditText chatField;


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
        conversation = data.getConversations().get(pos);
        return fragment;
    }

    public ConversationFragment() {
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View v = inflater.inflate(R.layout.fragment_main, container, false);

        log = (ListView) v.findViewById(R.id.chatLogView);
        log.setAdapter(new ArrayAdapter<String>(this.getActivity(),
                android.R.layout.simple_list_item_1,
                conversation.getMessages()));

        chatField = (EditText) v.findViewById(R.id.chatField);
        chatField.setOnKeyListener(new View.OnKeyListener() {
            public boolean onKey(View v, int keyCode, KeyEvent event) {
                if ((event.getAction() == KeyEvent.ACTION_DOWN) && (keyCode == KeyEvent.KEYCODE_ENTER)) {
                    sendMessage();
                    ((TextView)v).setText("");
                    return true;
                }
                return false;
            }
        } );


        Button sendButton = (Button) v.findViewById(R.id.chatSendButton);
        sendButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                sendMessage();
            }
        });
        return v;

    }

    private void sendMessage() {
        String text = chatField.getText().toString();
        if(text.length()!=0) {
            text = text.trim();
            chatField.setText("");
            conversation.addMessage(text);
            ((ArrayAdapter<String>) log.getAdapter()).notifyDataSetChanged();
            hideSoftKeyboard();

        }
    }

    private void hideSoftKeyboard() {
        View view = getActivity().getCurrentFocus();
        if (view != null) {
            InputMethodManager inputManager = (InputMethodManager) getActivity().getSystemService(Context.INPUT_METHOD_SERVICE);
            inputManager.hideSoftInputFromWindow(view.getWindowToken(), InputMethodManager.HIDE_NOT_ALWAYS);
        }
    }


    @Override
    public void onAttach(Activity activity) {
        super.onAttach(activity);
        int conID = getArguments().getInt(CONVERSATION_NUMBER);
        Conversation con = data.getConversations().get(conID);
        ((MainActivity) activity).onSectionAttached(con);
    }

}
