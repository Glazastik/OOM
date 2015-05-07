package se.chalmers.oomproject.oom;

import android.app.Notification;
import android.app.NotificationManager;
import android.os.Bundle;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.NotificationCompat;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBar;
import android.support.v7.app.ActionBarActivity;
import android.view.Menu;
import android.view.MenuItem;

import java.util.Timer;
import java.util.TimerTask;

public class MainActivity extends ActionBarActivity
        implements NavigationDrawerFragment.NavigationDrawerCallbacks {
    /**
     * Fragment managing the behaviors, interactions and presentation of the navigation drawer.
     */
    private NavigationDrawerFragment mNavigationDrawerFragment;
    /**
     * Used to store the last screen title. For use in {@link #restoreActionBar()}.
     */
    private CharSequence mTitle;
    private boolean isPerson = false;

    private static volatile boolean canNotify = true;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        //Get the singleton
        DataSingleton data = DataSingleton.getInstance();
        data.setContext(this);

        setContentView(R.layout.activity_main);

        mNavigationDrawerFragment = (NavigationDrawerFragment)
                getSupportFragmentManager().findFragmentById(R.id.navigation_drawer);
        mTitle = getTitle();

        // Set up the drawer.
        mNavigationDrawerFragment.setUp(
                R.id.navigation_drawer,
                (DrawerLayout) findViewById(R.id.drawer_layout));

    }

    @Override
    public void onNavigationDrawerItemSelected(int position) {
        // update the main content by replacing fragments
        FragmentManager fragmentManager = getSupportFragmentManager();
        clearBackStack();
        if (position == 0) {
            fragmentManager.beginTransaction()
                    .replace(R.id.container, LandingFragment.newInstance(), "landing_fragment")
                    .commit();
        } else {
            position--;
            fragmentManager.beginTransaction()
                    .replace(R.id.container, ConversationFragment.newInstance(position), "conversation_fragment")
                    .commit();
        }
    }

    public void onSectionAttached(String title, boolean b) {
        mTitle = title;
        isPerson = b;
    }

    public void onSectionAttached(Conversation con) {
        mTitle = con.getPerson().getName();
        isPerson = true;

    }

    public void onSectionAttached() {
        mTitle = getString(R.string.app_name);
        isPerson = false;
    }

    public void restoreActionBar() {
        ActionBar actionBar = getSupportActionBar();
        actionBar.setNavigationMode(ActionBar.NAVIGATION_MODE_STANDARD);
        actionBar.setDisplayShowTitleEnabled(true);
        actionBar.setTitle(mTitle);

    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        if (!mNavigationDrawerFragment.isDrawerOpen()) {
            // Only show items in the action bar relevant to this screen
            // if the drawer is not showing. Otherwise, let the drawer
            // decide what to show in the action bar.
            getMenuInflater().inflate(R.menu.main, menu);

            if (!isPersonFragment()) {
                //Hide person configuration if no person is up.
                menu.findItem(R.id.action_person).setVisible(false);
            }

            restoreActionBar();
            return true;
        }
        return super.onCreateOptionsMenu(menu);
    }

    private boolean isPersonFragment() {
        return isPerson;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    public void updateDrawer() {
        mNavigationDrawerFragment.updateDrawer();
    }

    private void clearBackStack() {
        FragmentManager manager = getSupportFragmentManager();
        if (manager.getBackStackEntryCount() > 0) {
            FragmentManager.BackStackEntry first = manager.getBackStackEntryAt(0);
            manager.popBackStack(first.getId(), FragmentManager.POP_BACK_STACK_INCLUSIVE);
        }
    }

    public void notification(String title, String message){
        if(canNotify) {
            NotificationCompat.Builder mBuilder =
                    new NotificationCompat.Builder(this)
                            .setSmallIcon(R.drawable.user)
                            .setContentTitle(title)
                            .setContentText(message);


            NotificationManager mNotifyMgr =
                    (NotificationManager) getSystemService(NOTIFICATION_SERVICE);

            Notification notif = mBuilder.build();
            notif.defaults = Notification.DEFAULT_ALL;
            notif.flags |= Notification.FLAG_SHOW_LIGHTS;
            notif.ledARGB = 0xff00ff00;
            notif.ledOnMS = 300;
            notif.ledOffMS = 1000;

            mNotifyMgr.notify(001, notif);
            canNotify = false;

            Timer timer = new Timer();
            timer.schedule(new TimerTask() {
                @Override
                public void run() {
                    canNotify = true;
                }
            }, 10000);
        }
    }

}
