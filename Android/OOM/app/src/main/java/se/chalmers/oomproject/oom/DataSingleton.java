package se.chalmers.oomproject.oom;

import android.app.Activity;

import java.util.ArrayList;

/**
 * Created by Anton on 2015-03-11.
 */
public class DataSingleton {

    private ArrayList<Person> persons;
    private ArrayList<Conversation> conversations;
    private ChatWrapper cw;
    private MessageWorker messageWorker;


    private static DataSingleton instance;

    private static int accountId = 0;

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
        cw = new ChatWrapper();
        cw.init();
        persons = new ArrayList<>();
        Person c1 = new Person(1, "Glaz");
        Person c2 = new Person(0, "Testelina");

        messageWorker = new MessageWorker(cw);
        messageWorker.start();
        while (!messageWorker.isAlive()) {
        }


        persons.add(c1);
        persons.add(c2);
        Account a1 = new Account(0, nextAccountId(), "1qb37r9krc35d08l0pdn0m4c8m@public.talk.google.com");
        c2.addAccount(a1);

        c1.addAccount(new Account(0, nextAccountId(), "google"));

        conversations = new ArrayList<>();
        Conversation con1 = new Conversation(c1);
        Conversation con2 = new Conversation(c2);
        conversations.add(con1);
        conversations.add(con2);


        cw.addPerson(c2.getId(), c2.getName());
        cw.addAccountToPerson(c2.getId(), a1.getId(), a1.getServiceType(), a1.getAddress());
        cw.connectService(0);
    }

    public void sendMessage(Message m) {
        for (Account a : m.getAccounts()) {
            cw.sendChatMessage(a.getId(), m.getText());
        }
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

    public int nextAccountId() {
        return accountId++;
    }
}
