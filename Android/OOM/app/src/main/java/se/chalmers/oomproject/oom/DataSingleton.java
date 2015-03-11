package se.chalmers.oomproject.oom;

import android.provider.ContactsContract;

/**
 * Created by Anton on 2015-03-11.
 */
public class DataSingleton {

    private static DataSingleton instance;
    private static DataSingleton getInstance(){
        if(instance != null){
            return instance;
        } else {
            instance = new DataSingleton();
            return instance;
        }
    }

    // Hidden constructor
    private DataSingleton() {

    }

}
