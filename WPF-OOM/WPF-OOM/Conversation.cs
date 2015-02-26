using System.Collections.ObjectModel;
using System.ComponentModel;

namespace WPF_OOM
{
    
    class Conversation : INotifyPropertyChanged
    {
        public Contact Contact { get; private set; }
        public ObservableCollection<Message> Messages { get; private set; }
        public event PropertyChangedEventHandler PropertyChanged;
        private string draftMessage;
        public string DraftMessage
        {
            get { return draftMessage;  }
            set
            {
                draftMessage = value;
                OnPropertyChanged("DraftMessage");
            }
        }

        public Conversation(Contact c)
        {
            Contact = c;
            Messages = new ObservableCollection<Message>();
        }

        public void AddMessage(Message m)
        {
            //TODO: Needs to validate that the sender of the message either is the user or the contact.
            Messages.Add(m);
        }
        protected void OnPropertyChanged(string name)
        {
            PropertyChangedEventHandler handler = PropertyChanged;
            if (handler != null)
            {
                handler(this, new PropertyChangedEventArgs(name));
            }
        }
        
    }
}
