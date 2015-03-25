package se.chalmers.oomproject.oom;

import android.app.Service;
import android.content.Context;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.GridLayout;
import android.widget.GridView;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.TextView;

import java.util.ArrayList;

/**
 * Created by meddan on 24/03/15.
 */
public class MessageAdapter extends ArrayAdapter<Message> {
    private Context context;
    public MessageAdapter(Context context, ArrayList<Message> messages) {
        super(context, 0, messages);
        this.context = context;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        // Get the data item for this position
        Message message = getItem(position);
        // Check if an existing view is being reused, otherwise inflate the view
        if (convertView == null) {
            convertView = LayoutInflater.from(getContext()).inflate(R.layout.item_message, parent, false);
            LinearLayout serviceList = (LinearLayout) convertView.findViewById(R.id.serviceList);
            for(IService s : message.getServices()){
                ImageView logoView = new ImageView(this.context);
                logoView.setImageDrawable(s.getLogo(this.context));
                logoView.setAdjustViewBounds(true);
                logoView.setMaxHeight(16);
                logoView.setMaxWidth(16);
                serviceList.addView(logoView);
            }
            TextView tvSender = (TextView) convertView.findViewById(R.id.tvSender);
            TextView tvText = (TextView) convertView.findViewById(R.id.tvText);
            tvSender.setText(message.getSender().getNickName());
            tvText.setText(message.getText());
        }
        return convertView;
    }
}
