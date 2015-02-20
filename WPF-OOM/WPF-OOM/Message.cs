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
        public Message(String s, Contact c, Service service)
        {
            Services = new ObservableCollection<Service>();
            Services.Add(service);
            sender = c;
            text = s;
        }
    }
}
