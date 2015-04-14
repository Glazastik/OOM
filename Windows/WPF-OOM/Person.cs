using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WPF_OOM
{
    class Person
    {
        private int id;
        private string name;
        public string FirstName { get; set; }
        public string LastName { get; set; }
        public string NickName { get; set; }
        public ObservableCollection<Account> Accounts;
        public Conversation Conversation;
        public Person(int id, string name)
        {
            this.Conversation = new Conversation(this);
            this.Accounts = new ObservableCollection<Account>();
            this.NickName = name;
            this.id = id;
            this.name = name;
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
            Accounts.Add(account);
        }

        public List<int> GetAccountIds()
        {
            List<int> ids = new List<int>();
            foreach (Account account in Accounts)
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
                foreach (Account acc in Accounts)
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
