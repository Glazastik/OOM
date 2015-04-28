package se.chalmers.oomproject.oom;

import android.content.Context;
import android.graphics.drawable.Drawable;

/**
 * Created by Glazastik on 24/04/15.
 */
public class Account {
    private int id;
    private int serviceType;
    private String address;

    private String serviceName;
    private String logoId, logo2Id;

    public Account(int id, int serviceType, String address) {
        this.id = id;
        this.serviceType = serviceType;
        this.address = address;

        switch (serviceType) {
            case 0:
                this.serviceName = "Google Hangouts";
                logoId = "google";
                logo2Id = "googledark";
                break;
            case 1:
                this.serviceName = "IRC";
                logoId = "irc";
                logo2Id = "ircdark";
                break;
            default:
                this.serviceName = "Unknown";
        }
    }

    public String getServiceName() {
        return serviceName;
    }

    public int getId() {
        return id;
    }

    public int getServiceType() {
        return serviceType;
    }

    public String getAddress() {
        return address;
    }

    public Drawable getLogo(Context c) {
        return c.getResources().getDrawable(c.getResources().getIdentifier(logoId, "drawable", c.getPackageName()));
    }

    public Drawable getOtherLogo(Context c) {
        return c.getResources().getDrawable(c.getResources().getIdentifier(logo2Id, "drawable", c.getPackageName()));
    }
}
