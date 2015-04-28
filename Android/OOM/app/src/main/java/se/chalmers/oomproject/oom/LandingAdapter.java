package se.chalmers.oomproject.oom;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;

import java.util.ArrayList;

/**
 * Created by meddan on 24/03/15.
 */
public class LandingAdapter extends ArrayAdapter<Conversation> {
    private Context context;

    public LandingAdapter(Context context, ArrayList<Conversation> conversations) {
        super(context, 0, conversations);
        this.context = context;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        // Get the data item for this position
        Conversation con = getItem(position);

        // Check if an existing view is being reused, otherwise inflate the view
        if (convertView == null) {
            convertView = LayoutInflater.from(getContext()).inflate(R.layout.item_landing, parent, false);

            TextView tvName = (TextView) convertView.findViewById(R.id.landing_item_name);
            TextView tvText = (TextView) convertView.findViewById(R.id.landing_item_text);
            tvName.setText(con.getContact().getNickName());
            if (con.getMessages().size() > 0) {
                tvText.setText(con.getMessages().get(con.getMessages().size() - 1).getText());
            } else {
                tvText.setText("Nothing to display here :(");
            }
        }
        return convertView;
    }
}
