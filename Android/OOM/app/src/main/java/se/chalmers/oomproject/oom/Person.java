package se.chalmers.oomproject.oom;

import java.util.ArrayList;

/**
 * Created by Glazastik on 24/04/15.
 */
public class Person {
    private int id;
    private String name;

    public String getFirstName() {
        return firstName;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public String getNickName() {
        return nickName;
    }

    public void setNickName(String nickName) {
        this.nickName = nickName;
    }

    public String getLastName() {
        return lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    private String firstName;
    private String nickName;
    private String lastName;
    private ArrayList<Account> accounts;

    public Person (int id, String name){
        this.accounts = new ArrayList<>();
        this.firstName = name;
        this.name = name;
        this.id = id;
    }

    public int getId(){
        return id;
    }

    public String getName(){
        return name;
    }

    public void addAccount(Account a){
        accounts.add(a);
    }

    public ArrayList<Integer> getAccountIds(){
        ArrayList<Integer> ids = new ArrayList<>();
        for(Account a : accounts){
            ids.add(a.getId());
        }
        return ids;
    }

    private static Person me;
    public static Person me (){
        if (me != null){
            return me;
        } else {
            me = new Person(-1, "Me");
            return me;
        }
    }
}
