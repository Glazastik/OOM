using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ManagedDLL;
using System.Runtime.InteropServices;

namespace TestConsole
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Title = "Test";

            Program prog = new Program();
            heh[0] = prog;

            //IntPtr intptr_delegate = Marshal.GetFunctionPointerForDelegate(new TestCallback(Cool));
            //Console.WriteLine(ManagedMessenger.CallingBack(intptr_delegate));

            InitializeMessenger();
            //Test2();

            Console.WriteLine("Press <Enter> to quit.");
            Console.ReadLine();
        }

        static void InitializeMessenger()
        {
            int[] message3 = new int[5];
            char[] namn = new char[256];
            namn[0] = 't';
            namn[1] = 'e';
            namn[2] = 's';
            namn[3] = 't';
            namn[4] = '\0';
            message3[0] = 1;

            ManagedMessenger messenger = new ManagedMessenger();

            Contact to;
            to.id = "cid";
            to.name = "Test";

            String data = "data";

            Message msg;
            msg.data = data;
            msg.cid = "cid";

            LoginData login;
            login.userName = "testUser";
            login.password = "qwerty";
            messenger.Login(Messenger.irc, login);

            messenger.SendMessage(Messenger.irc, msg);
            Console.WriteLine(messenger.GetMessage(Messenger.irc).data);
            
            List<Contact> contacts = messenger.GetContacts(Messenger.irc);
            Console.WriteLine(contacts[1].id);
        }

        public delegate void TestCallback(int arg1);

        public static void Cool(int i)
        {
            Console.WriteLine("it works");
            heh[i].OnReceivedMessage(EventArgs.Empty);
        }

        public Program()
        {
            ReceivedMessage += new EventHandler(MessageReceived);
        }

        public delegate void ReceivedMessageHandler(Object sender, EventArgs e);
        public event EventHandler ReceivedMessage;

        protected virtual void OnReceivedMessage(EventArgs e)
        {
            if (ReceivedMessage != null)
                ReceivedMessage(this, e);
        }

        public void MessageReceived(Object sender, EventArgs e)
        {
            Console.WriteLine("Message Received");
        }

        static Program[] heh = new Program[1];
    }
}
