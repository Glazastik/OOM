package se.chalmers.oomproject.oom;

import java.util.ArrayList;

/**
 * Created by Anton on 2015-03-11.
 */
public class Conversation {
    private Contact contact;
    private ArrayList<String> messages;

    public Conversation(Contact c){
        contact = c;
        messages = new ArrayList<>();
        for(int i = 0; i < 6; i++){
            messages.add("This is message " + (int) (29 * Math.random()));
        }
    }

    public ArrayList<String> getMessages(){ return messages; }
    public Contact getContact(){
        return contact;
    }
}
