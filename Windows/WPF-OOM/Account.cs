using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WPF_OOM
{
    public class Account
    {
        private int id;
        private int serviceType;
        private string address;
        public string ServiceName { get; set; }

        public Account(int id, int serviceType, string address)
        {
            switch (serviceType)
            {
                case 0:
                    this.ServiceName = "Google Hangouts";
                    break;
                case 1:
                    this.ServiceName = "IRC";
                    break;
            }
            this.id = id;
            this.serviceType = serviceType;
            this.address = address;
        }

        public int GetId()
        {
            return id;
        }

        public int GetServiceType()
        {
            return serviceType;
        }

        public string GetAddress()
        {
            return address;
        }
    }
}
