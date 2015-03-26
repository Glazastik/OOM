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
            uint message = 55;
            String message2 = "haha";
            int[] message3 = new int[5];
            char[] namn = new char[256];
            namn[0] = 't';
            namn[1] = 'e';
            namn[2] = 's';
            namn[3] = 't';
            namn[4] = '\0';
            message3[0] = 1;

            Messenger messeng = Messenger.google;
            ManagedMessenger messenger = new ManagedMessenger();

            Contact to;
            to.id = 1;
            to.name = "Test";

            Message msg;
            msg.messenger = Messenger.irc;
            msg.message = message2;
            msg.contact = to;

            LoginData login;
            login.userName = "testUser";
            login.password = "qwerty";
            messenger.Login(Messenger.irc, login);

            messenger.SendMessage(msg);
            Console.WriteLine(messenger.GetMessage().message);
            Console.WriteLine(messenger.GetMessage().contact.name);
            /*messenger.WriteMessageString(_messengerId, message2);

            Console.WriteLine(messenger.ReadMessageInt(_messengerId));
            Console.WriteLine(messenger.ReadMessageString(_messengerId));
            Console.WriteLine(messenger.ReadMessageCharArray(_messengerId));
            Console.WriteLine(messenger.ReadMessageIntArray(_messengerId)[2]);
            Console.WriteLine(messenger.ReadMessageStruct(_messengerId).test[1]);

            ManagedMessenger.DeleteMessenger(_messengerId); */
        }

        public delegate void TestCallback(int arg1);

        public static void Cool(int i)
        {
            Console.WriteLine("it works u fagget");
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
