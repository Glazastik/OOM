using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace WPF_OOM
{
    class Message
    {
        public string text { get; private set; }
        public Contact sender { get; private set; }
        public ObservableCollection<Service> Services { get; private set; }
        //Just for testing
        public Service Service { get; set; }
        //Just for testing
        public Message(String s, Contact c)
        {
            Services = new ObservableCollection<Service>();
            sender = c;
            text = s;
        }
    }
}
