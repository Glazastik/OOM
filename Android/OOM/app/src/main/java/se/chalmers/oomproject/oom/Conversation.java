package se.chalmers.oomproject.oom;

/**
 * Created by Anton on 2015-03-11.
 */
public class Conversation {
    private Contact contact;

    public Conversation(Contact c){
        contact = c;
    }

    public Contact getContact(){
        return contact;
    }
}
