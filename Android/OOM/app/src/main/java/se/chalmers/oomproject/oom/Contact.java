package se.chalmers.oomproject.oom;

import java.util.ArrayList;

/**
 * Created by Anton on 2015-03-11.
 */
public class Contact {

    private String firstName, nickName, lastName;
    private ArrayList<Service> services;

    public Contact(){
        services = new ArrayList<Service>();
    }

    public ArrayList<Service> getServices() {
        return services;
    }

    public void addService(Service service) {
        this.services.add(service);
    }

    public void setName(String first, String nick, String last){
        setFirstName(first);
        setNickName(nick);
        setLastName(last);
    }

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



}
