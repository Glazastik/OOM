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
    }

    public void addMessage(String m){

        ArrayList<IService> services = new ArrayList<IService>();
        services.add(new IService.Facebook());
        services.add(new IService.Steam());
        messages.add(new Message(m, services, this.contact));
        //messages.add(m);
    }

    public ArrayList<Message> getMessages(){ return messages; }
    public Contact getContact(){
        return contact;
    }
}
