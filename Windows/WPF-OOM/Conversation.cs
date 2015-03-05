using System.Collections.ObjectModel;
using System.ComponentModel;

namespace WPF_OOM
{
    
    public class Conversation : INotifyPropertyChanged
    {
        public Contact Contact { get; private set; }
        public ObservableCollection<Message> Messages { get; private set; }
        public event PropertyChangedEventHandler PropertyChanged;
        public Message DraftMessage { get; set; }

        public Conversation(Contact c)
        {
            Contact = c;
            Messages = new ObservableCollection<Message>();
            DraftMessage = new Message("", Contact, new ObservableCollection<Service>());
        }

        public void AddMessage(Message m)
        {
            //TODO: Needs to validate that the sender of the message either is the user or the contact.
            Messages.Add(m);
        }
        /*
        protected void OnPropertyChanged(string name)
        {
            PropertyChangedEventHandler handler = PropertyChanged;
            if (handler != null)
            {
                handler(this, new PropertyChangedEventArgs(name));
            }
        }
         */

        public void SendMessage()
        {
            if (!string.IsNullOrEmpty(DraftMessage.text))
            {
                this.Messages.Add(DraftMessage);
                Message dm = DraftMessage;
                this.DraftMessage = new Message("", Contact, dm.Services);
                DraftMessage.text = "";
            }
        }
        
    }
}
