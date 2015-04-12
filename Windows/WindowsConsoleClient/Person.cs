using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WindowsConsoleClient
{
    class Person
    {
        private int id;
        private string name;
        private List<Account> accounts;

        public Person(int id, string name)
        {
            this.id = id;
            this.name = name;
            accounts = new List<Account>();
        }

        public int GetId()
        {
            return id;
        }

        public string GetName()
        {
            return name;
        }

        public void AddAccount(Account account)
        {
            accounts.Add(account);
        }

        public List<int> GetAccountIds()
        {
            List<int> ids = new List<int>();
            foreach (Account account in accounts)
            {
                ids.Add(account.GetId());
            }
            return ids;
        }

        public Account GetAccount(int id)
        {
            Account account = new Account(-1, -1, "");
            if (GetAccountIds().Contains(id))
            {
                foreach (Account acc in accounts)
                {
                    if (acc.GetId() == id)
                    {
                        account = acc;
                    }
                }
            }
            else
            {
                Console.WriteLine("ERROR accountId does not exist");
            }
            return account;
        }
    }
}
