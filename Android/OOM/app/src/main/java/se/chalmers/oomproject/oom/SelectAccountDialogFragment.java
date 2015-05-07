package se.chalmers.oomproject.oom;

import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.support.v4.app.DialogFragment;
import android.util.Log;

import java.util.ArrayList;

/**
 * Created by meddan on 28/04/15.
 */
public class SelectAccountDialogFragment extends DialogFragment {
    private static Person person;

    public SelectAccountDialogFragment() {
    }

    public static SelectAccountDialogFragment newInstance(Person p) {
        person = p;
        return new SelectAccountDialogFragment();
    }

    private ArrayList<Account> mSelectedItems;

    public Dialog onCreateDialog(Bundle savedInstanceState) {
        Log.d("SADF", "ONCREATE");
        Log.d("SADF", "" + person.getSelectedAccounts().size());
        mSelectedItems = person.getSelectedAccounts();  // Where we track the selected items
        AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
        // Set the dialog title

        builder.setTitle("Select Services")
                // Specify the list array, the items to be selected by default (null for none),
                // and the listener through which to receive callbacks when items are selected
                .setMultiChoiceItems(AccountToChar(person.getAccounts()), GetSelectList(person.getAccounts(), person.getSelectedAccounts()),
                        new DialogInterface.OnMultiChoiceClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which,
                                                boolean isChecked) {
                                if (isChecked) {
                                    // If the user checked the item, add it to the selected items
                                    mSelectedItems.add(person.getAccounts().get(which));
                                } else if (mSelectedItems.contains(person.getAccounts().get(which))) {
                                    Log.d("SADF", "ELSEIF");
                                    // Else, if the item is already in the array, remove it
                                    mSelectedItems.remove(person.getAccounts().get(which));
                                }
                            }
                        })
                        // Set the action buttons
                .setPositiveButton("Accept", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int id) {
                        // User clicked OK, so save the mSelectedItems results somewhere
                        // or return them to the component that opened the dialog
                        person.setSelectedAccounts((ArrayList) mSelectedItems.clone());

                    }
                })
                .setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int id) {

                    }
                });

        return builder.create();
    }

    private CharSequence[] AccountToChar(ArrayList<Account> arrayList) {
        CharSequence[] cs = new CharSequence[arrayList.size()];
        int i = 0;
        for (Account a : arrayList) {
            cs[i] = a.getServiceName() + " " + a.getId();
            i++;
        }
        return cs;
    }

    private boolean[] GetSelectList(ArrayList<Account> accounts, ArrayList<Account> selected) {
        boolean[] bools = new boolean[accounts.size()];
        int i = 0;
        for (Account a : accounts) {
            bools[i] = selected.contains(a);
            i++;
        }
        return bools;
    }
}
