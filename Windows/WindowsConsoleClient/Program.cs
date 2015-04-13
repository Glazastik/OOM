using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;


namespace WindowsConsoleClient
{
    class Program
    {
        static int nextPersonId = 0;
        static int nextAccountId = 0;

        static void Main(string[] args)
        {
            ChatWrapper.Init();

            MessageWorker messageWorker = new MessageWorker();
            Thread messageThread = new Thread(messageWorker.DoWork);

            DebugPrintLine("Starting message thread.");
            messageThread.Start();

            // Wait for the debug thread to start
            while(!messageThread.IsAlive);

            DebugPrintLine("Connecting to Google Hangout (0).");
            ChatWrapper.ConnectService(0);

            TestLoop();

            ChatWrapper.Stop();
            messageWorker.StopWorking();
            messageThread.Join();
            DebugPrintLine("Message thread has terminated.");

            Console.Write("Press any key to exit...");
            Console.ReadKey();
        }

        static private void DebugPrint(string debugLine)
        {
            Console.Write("Main thread> " + debugLine);
        }

        static private void DebugPrintLine(string debugLine)
        {
            Console.WriteLine("Main thread> " + debugLine);
        }

        static private void TestLoop()
        {
            List<Person> persons = new List<Person>();
            // Add Kandidattestelina test account
            Person testPerson = new Person(nextPersonId, "Testelina");
            nextPersonId++;
            persons.Add(testPerson);
            ChatWrapper.AddPerson(testPerson);
            Account account = new Account(nextAccountId, 0, "1qb37r9krc35d08l0pdn0m4c8m@public.talk.google.com");
            nextAccountId++;
            testPerson.AddAccount(account);
            ChatWrapper.AddAccountToPerson(testPerson.GetId(), account);

            int choice;
            bool isRunning = true;
            while (isRunning)
            {
                PrintChoices();
                DebugPrintLine("Enter number:");
                string input = Console.ReadLine();
                if (Int32.TryParse(input, out choice))
                {
                    if (choice < 0 || choice > 4)
                    {
                        DebugPrintLine("INVALID INPUT");
                    }
                    else if (choice == 0)
                    {
                        isRunning = false;
                    }
                    else if (choice == 1)
                    {
                        PrintPersons(persons);   
                    }
                    else if (choice == 2)
                    {
                        AddPerson(persons);
                    }
                    else if (choice == 3)
                    {
                        AddAccountToPerson(persons);
                    }
                    else
                    {
                        SendMessage();
                    }
                }
                else
                {
                    DebugPrintLine("INVALID INPUT");
                }
            }
            Console.WriteLine();
        }

        static private void PrintChoices()
        {
            Console.WriteLine();
            DebugPrintLine("*************************");
            DebugPrintLine("1. Display persons");
            DebugPrintLine("2. Add person");
            DebugPrintLine("3. Add account to person");
            DebugPrintLine("4. Send message");
            DebugPrintLine("0. Exit");
            DebugPrintLine("*************************");
        }

        static private void PrintPersons(List<Person> persons)
        {
            Console.WriteLine();
            DebugPrintLine("Persons:");
            foreach (Person person in persons)
            {
                int personId = person.GetId();
                string name = person.GetName();
                List<int> accountIds = person.GetAccountIds();

                DebugPrintLine("-Person id:" + personId + " name:" + name);

                foreach (int accountId in accountIds)
                {
                    Account account = person.GetAccount(accountId);
                    int serviceType = account.GetServiceType();
                    string address = account.GetAddress();
                    DebugPrintLine("\t-Account id:" + accountId + " serviceType:" + serviceType + " address:" + address);
                }
            }
        }

        static private void AddPerson(List<Person> persons)
        {
            DebugPrintLine("Enter name:");
            string input = Console.ReadLine();
            Person person = new Person(nextPersonId, input);
            nextPersonId++;
            persons.Add(person);
            ChatWrapper.AddPerson(person);
        }

        static private void AddAccountToPerson(List<Person> persons)
        {
            DebugPrintLine("Enter Person id:");
            string input = Console.ReadLine();
            int id;
            if (Int32.TryParse(input, out id))
            {
                foreach (Person person in persons)
                {
                    int personId = person.GetId();
                    if (personId == id)
                    {
                        DebugPrintLine("Enter Account ServiceType:");
                        input = Console.ReadLine();
                        int serviceType;
                        if (Int32.TryParse(input, out serviceType))
                        {
                            DebugPrintLine("Enter Account Address:");
                            input = Console.ReadLine();
                            Account account = new Account(nextAccountId, serviceType, input);
                            nextAccountId++;
                            person.AddAccount(account);
                            ChatWrapper.AddAccountToPerson(personId, account);
                            return;
                        }
                    }
                }
            }
            DebugPrintLine("INVALID INPUT");
        }

        static private void SendMessage()
        {
            DebugPrintLine("Enter account id:");
            string input = Console.ReadLine();
            int accountId;
            if (Int32.TryParse(input, out accountId))
            {
                DebugPrintLine("Enter Message:");
                input = Console.ReadLine();
                ChatWrapper.SendChatMessage(accountId, input);
                return;
            }
            DebugPrintLine("INVALID INPUT");
        }
    }
}
