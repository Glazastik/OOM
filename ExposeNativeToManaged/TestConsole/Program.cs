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

            IntPtr intptr_delegate = Marshal.GetFunctionPointerForDelegate(new TestCallback(Cool));
            Console.WriteLine(ManagedMessenger.CallingBack(intptr_delegate));

            //Test1();
            Test2();

            Console.WriteLine("Press <Enter> to quit.");
            Console.ReadLine();
        }

        static void Test()
        {
            ManagedMessenger.Test();
        }

        static void Test1()
        {
            uint message = 55;
            String message2 = "test";
            //message_t message3;
           // message3.time = 77;
            //message_t.test = new int[];
            //message3.sender = "random";
            //message3.message = "Hejsan!";

            uint _messengerId = ManagedMessenger.CreateMessenger();
            Console.WriteLine(_messengerId);

            message_t2 message4 = ManagedMessenger.ReadMessage2(_messengerId);
            message_t3 message5 = ManagedMessenger.ReadMessage3(_messengerId);
            //message_t message6 = ManagedMessenger.ReadMessage(_messengerId);

            ManagedMessenger.WriteMessageInt(_messengerId, message);
            ManagedMessenger.WriteMessageString(_messengerId, message2);
            //ManagedMessenger.WriteMessageStruct(_messengerId, message3);
            ManagedMessenger.WriteMessageInt(_messengerId, (uint) message4.time);
            ManagedMessenger.WriteMessageString(_messengerId, Marshal.PtrToStringAnsi(message5.message));
            //ManagedMessenger.WriteMessageString(_messengerId, message5.message);
            //ManagedMessenger.WriteMessageStruct(_messengerId, message6);
            ManagedMessenger.DeleteMessenger(_messengerId);
        }

        public static void Test2()
        {
            int capacity = 32;
            IntPtr str = Marshal.AllocHGlobal(sizeof(char) * capacity);
            try
            {
                ManagedMessenger.Dummy2(str, capacity);
                String test = Marshal.PtrToStringUni(str);
                Console.WriteLine(test);
            }
            finally
            {
                // Free the unmanaged memory.
                Marshal.FreeHGlobal(str);
            }
            // Create a managed array.
            byte[] managedArray = new byte[4];
            // Initialize unmanged memory to hold the array.
            byte size = sizeof(byte) * 4;
            IntPtr pnt = Marshal.AllocHGlobal(size);

            try
            {

                ManagedMessenger.Dummy3(pnt, capacity);
                // Copy the unmanaged array back to another managed array.
                for (int i = 0; i < 4; i++)
                    managedArray[i] = (byte) Marshal.ReadByte(pnt, i);

                for (int i = 0; i < 4; i++)
                    Console.WriteLine(managedArray[i]);

            }
            finally
            {
                // Free the unmanaged memory.
                Marshal.FreeHGlobal(pnt);
            }

            int[] internalArray = new int[5];
            // Initialize unmanged memory to hold the array.
            size = sizeof(int)  + (sizeof(int) * 5);
            IntPtr pnt2 = Marshal.AllocHGlobal(size);

            try
            {

                ManagedMessenger.Dummy5(pnt2, capacity);

                int internalInt = Marshal.ReadInt32(pnt2, 0);

                // Copy the unmanaged array back to another managed array.
                for (int i = 0; i < internalArray.Length; i++)
                    internalArray[i] = Marshal.ReadInt32(pnt2, (i+1)*4);


                message_n temp;
                temp.time = internalInt;
                temp.test = internalArray;

                Console.WriteLine(temp.time);
                for (int i = 0; i < internalArray.Length; i++)
                    Console.WriteLine(temp.test[i]);

            }
            finally
            {
                // Free the unmanaged memory.
                Marshal.FreeHGlobal(pnt2);
            }

            Console.ReadLine();
        }

        private static IntPtr MarshalToPointer(message_t data)
        {
            IntPtr buf = Marshal.AllocHGlobal(
                Marshal.SizeOf(data));
            Marshal.StructureToPtr(data,
                buf, false);
            return buf;
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
