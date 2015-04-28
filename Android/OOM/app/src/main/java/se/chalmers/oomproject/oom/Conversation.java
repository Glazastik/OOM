package se.chalmers.oomproject.oom;

import java.util.ArrayList;

/**
 * Created by Anton on 2015-03-11.
 */
public class Conversation {
    private Contact contact;
    private ArrayList<Message> messages;

    public Conversation(Contact c){
        contact = c;
        messages = new ArrayList<>();
        ArrayList<IService> services = new ArrayList<IService>();
        services.add(new IService.Steam());
        for(int i = 0; i < 6; i++){
            messages.add(new Message("This is message " + (int) (29 * Math.random()),services,c));
        }
    }

    public void addMessage(Message m){
        //TODO: Validation
        messages.add(m);
    }

    public ArrayList<Message> getMessages(){ return messages; }
    public Contact getContact(){
        return contact;
    }
}