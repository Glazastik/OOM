package se.chalmers.oomproject.oom;

import android.util.Log;

import java.util.ArrayList;

/**
 * Created by meddan on 13/03/15.
 */
public class Message {
    private String text;
    private ArrayList<IService> services;
    private Contact sender;
    public Message(String message, ArrayList<IService> services, Contact sender){
        this.text = message;
        this.sender = sender;
        this.services = services;
    }
    public String getText(){
        return text;
    }
    public ArrayList<IService> getServices(){
        return services;
    }
    public Contact getSender(){
        return sender;
    }
}
