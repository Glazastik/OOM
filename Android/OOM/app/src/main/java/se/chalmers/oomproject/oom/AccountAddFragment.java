package se.chalmers.oomproject.oom;

import android.os.Bundle;
import android.support.v4.app.DialogFragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.TextView;

/**
 * Created by Glazastik on 29/04/15.
 */
public class AccountAddFragment extends DialogFragment {

    private static Person person;
    private EditText serviceText;
    private RadioGroup rg;

    public static AccountAddFragment newInstance(Person p){
        person = p;

        return new AccountAddFragment();
    }

    public AccountAddFragment(){

    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View v = inflater.inflate(R.layout.fragment_addaccount, container);

        rg = (RadioGroup) v.findViewById(R.id.radioServiceGroup);
        serviceText = (EditText) v.findViewById(R.id.editServiceType);

        Button addButton = (Button) v.findViewById(R.id.add_account_button);
        addButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int id = DataSingleton.getInstance().nextAccountId();
                int service = -1;
                if(rg.getCheckedRadioButtonId() == R.id.radioService0){
                    service = 0;
                } else if(rg.getCheckedRadioButtonId() == R.id.radioService1){
                    service = 1;
                }

                person.addAccount(new Account(id,service,serviceText.getText().toString().trim()));
                getDialog().dismiss();
            }
        });

        rg.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener()
        {
            @Override
            public void onCheckedChanged(RadioGroup group, int checkedId) {
                switch(checkedId){
                    case R.id.radioService0:
                        serviceText.setHint("Google Hangouts address:");
                        break;
                    case R.id.radioService1:
                        serviceText.setHint("IRC recipient nickname");
                        break;
                }
            }
        });

        getDialog().setTitle("Add a new account");
        rg.check(R.id.radioService0);


        return v;
    }

}
