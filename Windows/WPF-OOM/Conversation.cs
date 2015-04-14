using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Diagnostics;

namespace WPF_OOM
{
    
    public class Conversation : INotifyPropertyChanged
    {
        public Person Person { get; private set; }
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

        public Conversation(Person p)
        {
            Person = p;
            Messages = new ObservableCollection<Message>();
            //TODO: Change 2nd c.Services to new OC.
            DraftMessage = new DraftMessage(Person.Accounts, new ObservableCollection<Account>());
            Person.Accounts.CollectionChanged += PersonAccountChanged;
        }

        void PersonAccountChanged(object sender, System.Collections.Specialized.NotifyCollectionChangedEventArgs e)
        {
            var s = (ObservableCollection<Account>) sender;
            DraftMessage dm = new DraftMessage(s,DraftMessage.GetSelectedAccounts());
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
            if (!string.IsNullOrEmpty(DraftMessage.text) && DraftMessage.GetSelectedAccounts().Count != 0)
            {
                this.Messages.Add(DraftMessage.ToMessage());
                foreach (Account acc in DraftMessage.GetSelectedAccounts())
                {
                    ChatWrapper.SendChatMessage(acc.GetId(), DraftMessage.text);
                }
                
                DraftMessage dm = DraftMessage;
                this.DraftMessage = new DraftMessage(Person.Accounts, dm.GetSelectedAccounts());
            }
        }
        
    }
}
