using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WindowsConsoleClient
{
    class Account
    {
        private int id;
        private int serviceType;
        private string address;

        public Account(int id, int serviceType, string address)
        {
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
