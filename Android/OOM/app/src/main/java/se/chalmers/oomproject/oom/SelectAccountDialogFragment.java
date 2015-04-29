package se.chalmers.oomproject.oom;

import android.app.AlertDialog;
import android.app.Dialog;
import android.app.DialogFragment;
import android.content.DialogInterface;
import android.os.Bundle;

import java.util.ArrayList;

/**
 * Created by meddan on 28/04/15.
 */
public class SelectAccountDialogFragment extends DialogFragment {
    private Person p;
    public SelectAccountDialogFragment(){}
    public SelectAccountDialogFragment(Person p){
        this.p = p;
    }
    private ArrayList<Account> mSelectedItems;
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        mSelectedItems = p.getSelectedAccounts();  // Where we track the selected items
        AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
        // Set the dialog title

        builder.setTitle("Select Services")
                // Specify the list array, the items to be selected by default (null for none),
                // and the listener through which to receive callbacks when items are selected
                .setMultiChoiceItems(AccountToChar(p.getAccounts()), GetSelectList(p.getAccounts(), mSelectedItems),
                        new DialogInterface.OnMultiChoiceClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which,
                                                boolean isChecked) {
                                if (isChecked) {
                                    // If the user checked the item, add it to the selected items
                                    mSelectedItems.add(p.getAccounts().get(which));
                                } else if (mSelectedItems.contains(which)) {
                                    // Else, if the item is already in the array, remove it
                                    mSelectedItems.remove(Integer.valueOf(which));
                                }
                            }
                        })
                        // Set the action buttons
                .setPositiveButton("Accept", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int id) {
                        // User clicked OK, so save the mSelectedItems results somewhere
                        // or return them to the component that opened the dialog

                    }
                })
                .setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int id) {

                    }
                });

        return builder.create();
    }
    private CharSequence[] AccountToChar(ArrayList<Account> arrayList){
        CharSequence[] cs = new CharSequence[arrayList.size()];
        int i = 0;
        for(Account a : arrayList){
            cs[i] = a.getServiceName();
            i++;
        }
        return cs;
    }
    private boolean[] GetSelectList(ArrayList<Account> accounts, ArrayList<Account> selected){
        boolean[] bools = new boolean[accounts.size()];
        int i = 0;
        for(Account a : accounts){
            bools[i] = selected.contains(a);
            i++;
        }
        return bools;
    }
}
