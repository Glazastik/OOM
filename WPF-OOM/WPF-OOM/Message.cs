using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WPF_OOM
{
    class Message
    {
        public string text { get; private set; }
        public Contact sender { get; private set; }
        public Message(String s, Contact c)
        {
            text = s;
            sender = c;
        }
    }
}
