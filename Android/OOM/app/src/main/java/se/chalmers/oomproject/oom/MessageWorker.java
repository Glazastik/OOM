package se.chalmers.oomproject.oom;

import android.util.Log;

/**
 * Created by Glazastik on 05/05/15.
 */
public class MessageWorker extends Thread {
    private final int buffer_size = 4096;
    private volatile boolean isWorking;
    private int nextMessage;
    private ChatWrapper cw;

    public MessageWorker(ChatWrapper cw){
        isWorking = true;
        nextMessage = 0;
        this.cw = cw;
    }

    @Override
    public void run(){
        while(isWorking){
            if(cw.getNumMessages() > nextMessage){
                Log.d("Message", "Received a new message");

                byte[] payloadBuffer = new byte[buffer_size];
                int senderId = cw.readMessage(nextMessage, payloadBuffer);
                String message = payloadBuffer.toString();

                for(Conversation c : DataSingleton.getInstance().getConversations()){
                    if(c.getPerson().getId() == senderId){
                        int serviceId = cw.getServiceType(senderId);
                        c.addMessage(new Message(message,c.getPerson().getAccounts(), c.getPerson()));

                    }
                }
                nextMessage++;
                Log.d("message", "Message from " + senderId + " > " + message);
                try {
                    Thread.sleep(200);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public void stopWorking(){
        isWorking = false;
    }
}
