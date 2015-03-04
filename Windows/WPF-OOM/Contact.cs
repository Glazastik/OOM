using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WPF_OOM
{
    public class Contact
    {
        public string FirstName { get; set; }
        public string LastName { get; set; }
        public string NickName { get; set; }
        public ObservableCollection<Service> Services { get; private set; }
        public Dictionary<Service, String> Accounts { get; private set; } 
        public Contact()
        {
            Services = new ObservableCollection<Service>();
            Accounts = new Dictionary<Service, string>();
        }

        public void addService(Service s, String acc)
        {
            Services.Add(s);
            Accounts.Add(s,acc);
        }
    }
}
