using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WPF_OOM
{
    
    class Conversation
    {
        public Contact contact { get; private set; }
        public ObservableCollection<Message> messages { get; private set; }
        public Conversation(Contact c)
        {
            contact = c;
            messages = new ObservableCollection<Message>();
        }

        public void addMessage(Message m)
        {
            //TODO: Needs to validate that the sender of the message either is the user or the contact.
            messages.Add(m);
        }
    }
}
