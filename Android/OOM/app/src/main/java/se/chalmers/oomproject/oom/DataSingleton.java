package se.chalmers.oomproject.oom;

import android.app.Activity;

import java.util.ArrayList;

/**
 * Created by Anton on 2015-03-11.
 */
public class DataSingleton {

    private ArrayList<Person> persons;
    private ArrayList<Conversation> conversations;

    private static DataSingleton instance;

    public static DataSingleton getInstance() {
        if (instance != null) {
            return instance;
        } else {
            instance = new DataSingleton();
            return instance;
        }
    }

    // Hidden constructor
    private DataSingleton() {
        persons = new ArrayList<>();
        Person c1 = new Person(0, "Glaz");
        Person c2 = new Person(1, "Meddan");

        persons.add(c1);
        persons.add(c2);

        c1.addAccount(new Account(0,0,"google"));

        conversations = new ArrayList<>();
        Conversation con1 = new Conversation(c1);
        Conversation con2 = new Conversation(c2);
        conversations.add(con1);
        conversations.add(con2);
    }

    public ArrayList<Person> getPersons() {
        return persons;
    }

    public ArrayList<Conversation> getConversations() {
        return conversations;
    }

    public ArrayList<String> getConversationNames() {
        ArrayList<String> names = new ArrayList<>();
        for (Conversation c : conversations) {
            names.add(c.getPerson().getName());
        }
        return names;
    }

    public ArrayList<Message> getConversationMessages(int i) {
        return conversations.get(i).getMessages();
    }

    public void addNewPerson(Person c, Activity a) {
        this.persons.add(c);
        this.conversations.add(new Conversation(c));
        ((MainActivity) a).updateDrawer();
    }
}
