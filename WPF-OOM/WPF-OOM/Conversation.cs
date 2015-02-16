using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WPF_OOM
{
    
    class Conversation
    {
        public readonly Contact contact;
        public List<Message> messages { get; private set; } 

        public Conversation(Contact c)
        {
            contact = c;
            messages = new List<Message>();
        }
    }
}
