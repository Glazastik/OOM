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

            Test();
            //Test2();

            Console.WriteLine("Press <Enter> to quit.");
            Console.ReadLine();
        }

        static void Test()
        {
            uint message = 55;
            String message2 = "test";
            int[] message3 = new int[5];
            message3[0] = 1;
            //message_t message3;
           // message3.time = 77;
            //message_t.test = new int[];
            //message3.sender = "random";
            //message3.message = "Hejsan!";


            uint _messengerId = ManagedMessenger.CreateMessenger();
            Console.WriteLine(_messengerId);

            ManagedMessenger.WriteMessageInt(_messengerId, message);
            ManagedMessenger.WriteMessageString(_messengerId, message2);
            ManagedMessenger.WriteMessageIntArray(_messengerId, message3, 5);
            //ManagedMessenger.WriteMessageStruct(_messengerId, message3);

            Console.WriteLine(ManagedMessenger.ReadMessageInt(_messengerId));
            Console.WriteLine(ManagedMessenger.ReadMessageString(_messengerId));
            Console.WriteLine(ManagedMessenger.ReadMessageCharArray(_messengerId));
            Console.WriteLine(ManagedMessenger.ReadMessageIntArray(_messengerId)[2]);
            Console.WriteLine(ManagedMessenger.ReadMessageStruct(_messengerId).test[1]);

            ManagedMessenger.DeleteMessenger(_messengerId);
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
