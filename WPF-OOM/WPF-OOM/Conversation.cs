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
        public readonly Contact contact;
        public ObservableCollection<Message> messages { get; private set; } 

        public Conversation(Contact c)
        {
            contact = c;
            messages = new ObservableCollection<Message>();
        }

        public void addMessage(Message m)
        {
            messages.Add(m);
        }
    }
}
