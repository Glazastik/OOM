package se.chalmers.oomproject.oom;

import java.util.ArrayList;

/**
 * Created by meddan on 13/03/15.
 */
public class Message {
    private String text;
    private ArrayList<Account> accounts;
    private Person sender;
    public Message(String message, ArrayList<Account> accounts, Person sender){
        this.text = message;
        this.sender = sender;
        this.accounts = accounts;
    }
    public String getText(){
        return text;
    }
    public ArrayList<Account> getAccounts(){
        return accounts;
    }
    public Person getSender(){
        return sender;
    }
}
