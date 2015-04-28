package se.chalmers.oomproject.oom;

import java.util.ArrayList;

/**
 * Created by Anton on 2015-03-11.
 */
public class Conversation {
    private Person person;
    private ArrayList<Message> messages;

    public Conversation(Person p){
        person = p;
        messages = new ArrayList<>();
    }

    public void addMessage(Message m){
        //TODO: Validation
        messages.add(m);
    }

    public ArrayList<Message> getMessages(){ return messages; }
    public Person getPerson(){
        return person;
    }
}