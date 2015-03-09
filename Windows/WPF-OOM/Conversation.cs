using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Diagnostics;

namespace WPF_OOM
{
    
    public class Conversation : INotifyPropertyChanged
    {
        public Contact Contact { get; private set; }
        public ObservableCollection<Message> Messages { get; private set; }
        public event PropertyChangedEventHandler PropertyChanged;
        private DraftMessage _draftMessage;

        public DraftMessage DraftMessage
        {
            get { return _draftMessage; }
            set
            {
                _draftMessage = value;
                OnPropertyChanged("DraftMessage");
            }
        }

        public Conversation(Contact c)
        {
            Contact = c;
            Messages = new ObservableCollection<Message>();
            //TODO: Change 2nd c.Services to new OC.
            DraftMessage = new DraftMessage(c.Services, new ObservableCollection<Service>());
            Contact.Services.CollectionChanged += ContactServicesChanged;
        }

        void ContactServicesChanged(object sender, System.Collections.Specialized.NotifyCollectionChangedEventArgs e)
        {
            var s = (ObservableCollection<Service>) sender;
            DraftMessage dm = new DraftMessage(s,DraftMessage.GetServices());
            this.DraftMessage = dm;
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

        public void SendMessage()
        {
            if (!string.IsNullOrEmpty(DraftMessage.text) && DraftMessage.GetServices().Count != 0)
            {
                this.Messages.Add(DraftMessage.ToMessage());
                DraftMessage dm = DraftMessage;
                this.DraftMessage = new DraftMessage(Contact.Services, dm.GetServices());
            }
        }
        
    }
}
