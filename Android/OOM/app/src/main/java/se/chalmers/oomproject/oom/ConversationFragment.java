package se.chalmers.oomproject.oom;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.Fragment;
import android.content.Context;
import android.os.Bundle;
import android.support.v4.app.FragmentManager;
import android.support.v7.app.ActionBar;
import android.support.v7.app.ActionBarActivity;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.MenuItem;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.view.inputmethod.InputMethodManager;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.PopupMenu;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;

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
    public void onCreateOptionsMenu(
            Menu menu, MenuInflater inflater) {
        Log.d("CF", "inflating conversation actionbar");
        inflater.inflate(R.menu.conversation, menu);
    }
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View v = inflater.inflate(R.layout.fragment_main, container, false);
        this.setHasOptionsMenu(true);
        log = (ListView) v.findViewById(R.id.chatLogView);
        log.setAdapter(new MessageAdapter(this.getActivity(),
                conversation.getMessages()));
        chatField = (EditText) v.findViewById(R.id.chatField);
        chatField.setOnKeyListener(new View.OnKeyListener() {
            public boolean onKey(View v, int keyCode, KeyEvent event) {
                if ((event.getAction() == KeyEvent.ACTION_DOWN) && (keyCode == KeyEvent.KEYCODE_ENTER)) {
                    sendMessage();
                    ((TextView) v).setText("");
                    return true;
                }
                return false;
            }
        });


        Button sendButton = (Button) v.findViewById(R.id.chatSendButton);
        Button accountButton = (Button) v.findViewById(R.id.edit_item_btn);

        sendButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                sendMessage();
            }
        });
        getActivity().getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_STATE_ALWAYS_HIDDEN);

        String title = conversation.getPerson().getName();
        getActionBar().setTitle(title);
        setHasOptionsMenu(true);

        return v;

    }
    private void openServiceSelection(){
        

    }

    private void sendMessage() {
        String text = chatField.getText().toString().trim();
        ArrayList<Account> accounts = new ArrayList<Account>();
        if (text.length() != 0) {
            chatField.setText("");
            conversation.addMessage(new Message(text, accounts, Person.me()));
            ((ArrayAdapter<Message>) log.getAdapter()).notifyDataSetChanged();
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

    private ActionBar getActionBar() {
        return ((ActionBarActivity) getActivity()).getSupportActionBar();
    }

    @Override
    public void onResume() {
        super.onResume();

        getView().setFocusableInTouchMode(true);
        getView().requestFocus();
        getView().setOnKeyListener(new View.OnKeyListener() {
            @Override
            public boolean onKey(View v, int keyCode, KeyEvent event) {

                if (event.getAction() == KeyEvent.ACTION_UP && keyCode == KeyEvent.KEYCODE_BACK) {
                    FragmentManager fragmentManager = getActivity().getSupportFragmentManager();
                    fragmentManager.beginTransaction()
                            .replace(R.id.container, LandingFragment.newInstance())
                            .commit();
                    return true;
                }
                return false;
            }
        });
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {

        if(item.getItemId() == R.id.action_person){
            FragmentManager fragmentManager = getActivity().getSupportFragmentManager();
            fragmentManager.beginTransaction()
                    .replace(R.id.container, PersonEditFragment.newInstance(conversation.getPerson())).addToBackStack("conversation")
                    .commit();
        }

        return super.onOptionsItemSelected(item);
    }
}
