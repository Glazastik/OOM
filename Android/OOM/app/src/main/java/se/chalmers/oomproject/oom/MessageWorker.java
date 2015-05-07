package se.chalmers.oomproject.oom;

import android.support.v4.app.FragmentManager;
import android.support.v7.app.ActionBarActivity;
import android.util.Log;

/**
 * Created by Glazastik on 05/05/15.
 */
public class MessageWorker extends Thread {
    private final int buffer_size = 4096;
    private volatile boolean isWorking;
    private int nextMessage;
    private ChatWrapper cw;
    private DataSingleton data;


    public MessageWorker(ChatWrapper cw) {
        isWorking = true;
        nextMessage = 0;
        this.cw = cw;
    }

    @Override
    public void run() {
        while (isWorking) {
            if (cw.getNumMessages() > nextMessage) {
                if(data == null){
                    data = DataSingleton.getInstance();
                }


                Log.d("Message", "Received a new message");

                byte[] payloadBuffer = new byte[buffer_size];
                int senderId = cw.readMessage(nextMessage, payloadBuffer);

                String message = new String(payloadBuffer);

                for (Conversation c : data.getConversations()) {
                    if (c.getPerson().getId() == senderId) {
                        int serviceId = cw.getServiceType(senderId);
                        c.addMessage(new Message(message, c.getPerson().getAccounts(), c.getPerson()));

                        FragmentManager fm = ((ActionBarActivity)data.getContext()).getSupportFragmentManager();
                        ConversationFragment conFrag = (ConversationFragment)fm.findFragmentByTag("conversation_fragment");
                        if (conFrag != null && conFrag.isVisible()) {
                            conFrag.update(null);
                        } else if(conFrag == null || conFrag.isPaused() || !conFrag.isVisible() || conFrag.getConversation().getPerson() != c.getPerson()){
                            data.notification("OOM - " + c.getPerson().getName(), message);
                        }
                    }
                }
                nextMessage++;
                Log.d("message", "Message from " + senderId + " > " + message);

            }

            try {
                Thread.sleep(200);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public void stopWorking() {
        isWorking = false;
    }
}
