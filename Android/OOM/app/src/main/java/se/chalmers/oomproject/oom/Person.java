package se.chalmers.oomproject.oom;

import java.util.ArrayList;

/**
 * Created by Glazastik on 24/04/15.
 */
public class Person {
    private int id;
    private String name;

    private ArrayList<Account> accounts;

    public Person(int id, String name) {
        this.accounts = new ArrayList<>();
        this.name = name;
        this.id = id;
    }

    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void addAccount(Account a) {
        accounts.add(a);
    }

    public ArrayList<Integer> getAccountIds() {
        ArrayList<Integer> ids = new ArrayList<>();
        for (Account a : accounts) {
            ids.add(a.getId());
        }
        return ids;
    }

    private static Person me;

    public static Person me() {
        if (me != null) {
            return me;
        } else {
            me = new Person(-1, "Me");
            return me;
        }
    }
}