using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace WPF_OOM
{
    public interface IMessage
    {
        string text { get; set; }
        Contact sender { get; }
        ObservableCollection<Service> Services { get; }
    }
    public class Message : IMessage
    {
        public string text { get; set; }
        public Contact sender { get; private set; }
        public ObservableCollection<Service> Services { get; private set; }
        public Message(String s, Contact c, Service service)
        {
            Services = new ObservableCollection<Service>();
            Services.Add(service);
            sender = c;
            text = s;
        }

        public Message(String s, Contact c, ObservableCollection<Service> services)
        {
            Services = services;
            sender = c;
            text = s;
        }
    }

    public class DraftMessage
    {
        public DraftMessage(ObservableCollection<Service> services, ObservableCollection<Service> selectedServices )
        {
            Services = new ObservableCollection<DraftService>();
            foreach (Service s in services)
            {
                Services.Add(selectedServices.Contains(s) ? new DraftService(s, true) : new DraftService(s, false));
            }
        }

        public Message ToMessage()
        {
            
            return new Message(text, Contact.Me, this.GetServices() );

        }

        public ObservableCollection<Service> GetServices()
        {
            ObservableCollection<Service> services = new ObservableCollection<Service>();
            foreach (DraftService s in Services)
            {
                if (s.Selected)
                {
                    services.Add(s.Service);
                }
            }
            return services;
        } 

        public string text { get; set; }

        public Contact sender { get; private set; }

        public ObservableCollection<DraftService> Services { get; private set; } 
    }
}
