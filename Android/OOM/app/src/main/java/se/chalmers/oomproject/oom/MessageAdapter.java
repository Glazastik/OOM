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
public class MessageAdapter extends ArrayAdapter<Message> {
    public MessageAdapter(Context context, ArrayList<Message> messages) {
        super(context, 0, messages);
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        // Get the data item for this position
        Message message = getItem(position);
        // Check if an existing view is being reused, otherwise inflate the view
        if (convertView == null) {
            convertView = LayoutInflater.from(getContext()).inflate(R.layout.item_message, parent, false);
        }
        // Lookup view for data population
        TextView tvSender = (TextView) convertView.findViewById(R.id.tvSender);
        TextView tvText = (TextView) convertView.findViewById(R.id.tvText);
        // Populate the data into the template view using the data object
        tvSender.setText(message.getSender().getNickName());
        tvText.setText(message.getText());
        // Return the completed view to render on screen
        return convertView;
    }
}
