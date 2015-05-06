package se.chalmers.oomproject.oom;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.support.v4.app.FragmentManager;
import android.support.v7.app.ActionBar;
import android.support.v7.app.ActionBarActivity;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.view.inputmethod.InputMethodManager;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;

import java.util.ArrayList;

/**
 * Created by Anton on 2015-03-11.
 */
public class ConversationFragment extends android.support.v4.app.Fragment implements Updateable{

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

    private void openServiceSelection() {
        FragmentManager fragmentManager = getActivity().getSupportFragmentManager();
        SelectAccountDialogFragment.newInstance(this.conversation.getPerson()).show(fragmentManager, "service_select");

    }

    private void sendMessage() {
        String text = chatField.getText().toString().trim();
        ArrayList<Account> accounts = conversation.getPerson().getSelectedAccounts();
        if (text.length() != 0) {
            chatField.setText("");
            Message m = new Message(text, accounts, Person.me());
            conversation.addMessage(m);
            updateMessageList();
            data.sendMessage(m);
            hideSoftKeyboard();
        }
    }

    public void updateMessageList(){

        new Thread(new Runnable(){
            @Override
            public void run() {
                log.post(new Runnable() {
                    @Override
                    public void run() {
                        ((ArrayAdapter<Message>) log.getAdapter()).notifyDataSetChanged();
                    }
                });
            }
        }){
        }.start();

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

        if (item.getItemId() == R.id.action_person) {
            FragmentManager fragmentManager = getActivity().getSupportFragmentManager();
            fragmentManager.beginTransaction()
                    .replace(R.id.container, PersonEditFragment.newInstance(conversation.getPerson())).addToBackStack("conversation")
                    .commit();
        } else if (item.getItemId() == R.id.serviceBtn) {
            Log.d("CF", "service button");
            openServiceSelection();
        }

        return super.onOptionsItemSelected(item);
    }

    @Override
    public void update(Object object) {
        updateMessageList();
    }

}
