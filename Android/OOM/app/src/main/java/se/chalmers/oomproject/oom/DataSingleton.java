package se.chalmers.oomproject.oom;

import android.provider.ContactsContract;

import java.util.ArrayList;

/**
 * Created by Anton on 2015-03-11.
 */
public class DataSingleton {

    private ArrayList<Contact> contacts;
    private ArrayList<Conversation> conversations;

    private static DataSingleton instance;
    public static DataSingleton getInstance(){
        if(instance != null){
            return instance;
        } else {
            instance = new DataSingleton();
            return instance;
        }
    }

    // Hidden constructor
    private DataSingleton() {
        contacts = new ArrayList<>();
        Contact c1 = new Contact();
        c1.setName("Anton", "Glaz", "Myrholm");
        Contact c2 = new Contact();
        c2.setName("Christoffer", "Meddan", "Medin");

        contacts.add(c1);
        contacts.add(c2);

        conversations = new ArrayList<>();
        Conversation con1 = new Conversation(c1);
        Conversation con2 = new Conversation(c2);
        conversations.add(con1);
        conversations.add(con2);
    }

    public ArrayList<Contact> getContacts() {
        return contacts;
    }

    public ArrayList<Conversation> getConversations() {
        return conversations;
    }

    public String[] getConversationNames(){
        ArrayList<String> names = new ArrayList<>();
        for(Conversation c : conversations){
            names.add(c.getContact().getNickName());
        }
        return names.toArray(new String[names.size()]);
    }

    public ArrayList<String> getConversationMessages(int i) {
        return conversations.get(i).getMessages();
    }

}
