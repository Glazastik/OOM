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
        public string text { get; set; }

        public Contact sender { get; private set; }

        public ObservableCollection<DraftService> Services { get; private set; }

        //Creates a new draft message and with a list of services and a list that should be a subset of those services.
        //If a service is in the subset, but not the whole set it will not be added.
        //If a service is in both it will be selected, if it is in just the set it will not be selected.
        public DraftMessage(ObservableCollection<Account> accounts, ObservableCollection<Service> selectedServices )
        {
            Services = new ObservableCollection<DraftService>();
            Dictionary<Service,Account> sd = new Dictionary<Service, Account>();
            foreach (Account acc in accounts)
            {
                sd.Add(ChatWrapper.GetServiceByServiceType(ChatWrapper.GetServiceType(acc.GetId())),acc);
            }
            foreach (var i in sd)
            {
                Services.Add(selectedServices.Contains(i.Key) ? new DraftService(i.Key, true, i.Value) : new DraftService(i.Key, false, i.Value));
            }
        }

        public Message ToMessage()
        {
            
            return new Message(text, Contact.Me, this.GetSelectedServices());

        }

        public ObservableCollection<Service> GetSelectedServices()
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
    }
}
