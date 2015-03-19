using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace ManagedDLL
{
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    public struct message_t
    {
        public int time;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 5, ArraySubType = UnmanagedType.I4)]
        public int[] test;
    }

    public enum Messenger
    {
        irc = 0,
        google = 1,
        facebook = 2
    };

    public enum Message_type
    {
        text = 0,
    };

    #region structures

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    public struct message_header
    {
        public int size;
        public int leftOvers;
        public int type;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    public struct message_body
    {
        public int id;
        public int index;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256, ArraySubType = UnmanagedType.U2)]
        public char[] message;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    public struct message_data
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256, ArraySubType = UnmanagedType.U2)]
        public char[] message;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    public struct internal_contact
    {
        public int id;
        public int length;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256, ArraySubType = UnmanagedType.U2)]
        public char[] name;
    }

    public struct Contact
    {
        public int id;
        public String name;
    }

    public struct Message
    {
        public Messenger messenger;
        public String message;
        public Contact contact;
    }

    #endregion

    public class ManagedMessenger
    {

        #region NativeDLL imports

        //
        // Creating a messenger with ID
        //
        [DllImport("NativeDLL.dll", EntryPoint = "AddMessenger", CallingConvention = CallingConvention.Cdecl)]
        protected static extern uint _AddMessenger(uint messengerId);

        [DllImport("NativeDLL.dll", EntryPoint = "DeleteMessenger", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void _DeleteMessenger(uint messengerId);

        //
        // Writing data
        //
        [DllImport("NativeDLL.dll", EntryPoint = "WriteMessageInt", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void _WriteMessageInt(uint messengerId, uint message);

        [DllImport("NativeDLL.dll", EntryPoint = "WriteMessageString", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void _WriteMessageString(uint messengerId, String message);

        [DllImport("NativeDLL.dll", EntryPoint = "WriteMessageIntArray", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void _WriteMessageIntArray(uint messengerId, int[] message, int capacity);

        [DllImport("NativeDLL.dll", EntryPoint = "WriteMessageStruct", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void _WriteMessageStruct(uint messengerId, message_t message);

        //
        // Reading data
        //
        [DllImport("NativeDLL.dll", EntryPoint = "ReadMessageInt", CallingConvention = CallingConvention.Cdecl)]
        public static extern int _ReadMessageInt(uint messengerId);

        [DllImport("NativeDLL.dll", EntryPoint = "ReadMessageString", CallingConvention = CallingConvention.Cdecl)]
        public static extern void _ReadMessageString(uint messengerId, IntPtr str, int capacity);

        [DllImport("NativeDLL", EntryPoint = "ReadMessageIntArray", CallingConvention = CallingConvention.Cdecl)]
        public static extern void _ReadMessageIntArray(uint messengerId, IntPtr pnt, int capacity);

        [DllImport("NativeDLL", EntryPoint = "ReadMessageCharArray", CallingConvention = CallingConvention.Cdecl)]
        public static extern void _ReadMessageCharArray(uint messengerId, IntPtr pnt, int capacity);

        [DllImport("NativeDLL", EntryPoint = "ReadMessageStruct", CallingConvention = CallingConvention.Cdecl)]
        public static extern void _ReadMessageStruct(uint messengerId, IntPtr pnt);


        //
        // Sending messages
        //
        [DllImport("NativeDLL", EntryPoint = "SendMessageHeader", CallingConvention = CallingConvention.Cdecl)]
        public static extern void _SendMessageHeader(message_header header);

        [DllImport("NativeDLL", EntryPoint = "SendMessageBody", CallingConvention = CallingConvention.Cdecl)]
        public static extern void _SendMessageBody(message_body body);

        [DllImport("NativeDLL", EntryPoint = "SendMessageContact", CallingConvention = CallingConvention.Cdecl)]
        public static extern void _SendMessageBody(internal_contact contact);

        [DllImport("NativeDLL", EntryPoint = "_SendMessage", CallingConvention = CallingConvention.Cdecl)]
        public static extern void _SendMessage(uint messengerId);

        //
        // Getting messages
        //
        [DllImport("NativeDLL", EntryPoint = "GetMessageData", CallingConvention = CallingConvention.Cdecl)]
        public static extern void _GetMessageData(IntPtr body);

        [DllImport("NativeDLL", EntryPoint = "GetMessageHeader", CallingConvention = CallingConvention.Cdecl)]
        public static extern void _GetMessageHeader(IntPtr header);

        [DllImport("NativeDLL", EntryPoint = "GetMessageContact", CallingConvention = CallingConvention.Cdecl)]
        public static extern void _GetMessageContact(IntPtr contact);

        [DllImport("NativeDLL", EntryPoint = "HasMessageData", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool _HasMessageData();

        [DllImport("NativeDLL", EntryPoint = "_GetMessage", CallingConvention = CallingConvention.Cdecl)]
        public static extern uint _GetMessage();


        //
        // Other functions
        //
        [DllImport("NativeDLL", EntryPoint = "HasMessage", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool _HasMessage();

        [DllImport("NativeDLL", EntryPoint = "CallingBack", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool _CallingBack(IntPtr p);

        #endregion

        private int _messageId;

        private Messenger[] messengers;
        private int numberOfMessengers;

        //
        // Creating Messenger
        //
        public ManagedMessenger()
        {
            messengers = new Messenger[3];
            _messageId = 0;
        }

        public void AddMessenger(Messenger messenger)
        {
            _AddMessenger((uint)messenger);
            messengers[numberOfMessengers] = messenger; 
        }

        public void DeleteMessenger(Messenger messenger)
        {
            _DeleteMessenger((uint)messenger);
        }

        //
        // Send message
        //
        public void SendMessage(Message message)
        {
            char[] mess = message.message.ToCharArray();
            int size = mess.Length;
            int sizeQB = size / 256;
            int leftOvers = size % 256;

            //Send message header
            message_header header;
            header.size = size;
            header.leftOvers = leftOvers;
            header.type = 0;
            _SendMessageHeader(header);

            //Send message body
            message_body temp;
            int i;
            for (i = 0; i < sizeQB; i++ )
            {
                temp.id = _messageId;
                temp.index = i;
                temp.message = new char[256];
                for (int j = 0; j < 256; j++ )
                {
                    temp.message[j] = mess[(j * 256) + j];
                }
                _SendMessageBody(temp);
            }
            message_body temp2;
            temp2.id = _messageId;
            temp2.index = i;
            temp2.message = new char[256];
            for (i = 0; i < leftOvers; i++)
            {
                temp2.message[i] = mess[(sizeQB * 256) + i];
            }
            _SendMessageBody(temp2);

            //Send message

            _SendMessage((uint)message.messenger, message.contact);
            _messageId++;
        }
        //
        // Get message
        //
        public Message GetMessage()
        {         
            Messenger messenger = (Messenger) _GetMessage();
            internal_contact contact = ReadMessageContact();
            message_header header = ReadMessageHeader();
            String str = "";
            int i = 0;
            while(_HasMessageData())
            {
                message_data temp = ReadMessageData();
                String s;
                if(i < header.size) {
                    s = new String(temp.message, 0, 256);
                } else {
                    s = new String(temp.message, 0, header.leftOvers);
                }
                str += s;
                i++;
            }
            Message message;
            message.messenger = messenger;
            message.message = str;
            message.contact = toContact(contact);
            return message;
        }

        private Contact toContact(internal_contact contact)
        {
            Contact temp;
            temp.id = contact.id;
            temp.name = new String(contact.name, 0, contact.length);
            return temp;
        }

        private static message_header ReadMessageHeader()
        {
            // Initialize unmanged memory to hold the array.
            int size = sizeof(int) + sizeof(int) + sizeof(int);
            IntPtr pnt = Marshal.AllocHGlobal(size);
            message_header managedStruct;
            try
            {
                ManagedMessenger._GetMessageHeader(pnt);
                managedStruct.size = Marshal.ReadInt32(pnt, 0);
                managedStruct.leftOvers = Marshal.ReadInt32(pnt, 4);
                managedStruct.type = Marshal.ReadInt32(pnt, 8);
            }
            finally
            {
                // Free the unmanaged memory.
                Marshal.FreeHGlobal(pnt);
            }
            return managedStruct;
        }

        private static internal_contact ReadMessageContact()
        {
            char[] internalArray = new char[256];

            // Initialize unmanged memory to hold the array.
            int size = sizeof(int) + sizeof(int) + (sizeof(char) * 256);
            IntPtr pnt = Marshal.AllocHGlobal(size);
            internal_contact managedStruct;
            try
            {
                ManagedMessenger._GetMessageContact(pnt);
                int id = Marshal.ReadInt32(pnt, 0);
                int length = Marshal.ReadInt32(pnt, 4);
                // Copy the unmanaged array back to another managed array.
                for (int i = 0; i < internalArray.Length; i++)
                {
                    internalArray[i] = (char)Marshal.ReadInt16(pnt, (i + 4) * 2);
                }
                managedStruct.id = id;
                managedStruct.length = length;
                managedStruct.name = internalArray;
            }
            finally
            {
                // Free the unmanaged memory.
                Marshal.FreeHGlobal(pnt);
            }
            return managedStruct;
        }

        private static message_data ReadMessageData()
        {
            char[] internalArray = new char[256];

            // Initialize unmanged memory to hold the array.
            int size = (sizeof(char) * 256);
            IntPtr pnt = Marshal.AllocHGlobal(size);
            message_data managedStruct;
            try
            {
                ManagedMessenger._GetMessageData(pnt);

                // Copy the unmanaged array back to another managed array.
                for (int i = 0; i < internalArray.Length; i++)
                {
                    internalArray[i] = (char)Marshal.ReadInt16(pnt, i * 2);
                }
                managedStruct.message = internalArray;
            }
            finally
            {
                // Free the unmanaged memory.
                Marshal.FreeHGlobal(pnt);
            }
            return managedStruct;
        }

        //
        // Writing data
        //
        public void WriteMessageInt(Messenger messenger, uint message)
        {
            _WriteMessageInt((uint)messenger, message);
        }

        public static void WriteMessageString(uint _messengerId, String message)
        {
            _WriteMessageString(_messengerId, message);
        }

        public static void WriteMessageStruct(uint _messengerId, message_t message)
        {
            _WriteMessageStruct(_messengerId, message);
        }

        public static void WriteMessageIntArray(uint _messengerId, int[] message, int capacity)
        {
            _WriteMessageIntArray(_messengerId, message, capacity);
        }
                                                            
        //
        // Reading data
        //
        public static int ReadMessageInt(uint _messengerId)
        {
            return _ReadMessageInt(_messengerId);
        }

        public static string ReadMessageString(uint _messengerId)
        {
            int capacity = 32;
            IntPtr _str = Marshal.AllocHGlobal(sizeof(char) * capacity);
            String str;
            try
            {
                ManagedMessenger._ReadMessageString(_messengerId, _str, capacity);
                str = Marshal.PtrToStringUni(_str);
            }
            finally
            {
                // Free the unmanaged memory.
                Marshal.FreeHGlobal(_str);
            }
            return str;
        }

        public static char[] ReadMessageCharArray(uint _messengerId)
        {
            int capacity = 32;
            // Create a managed array.
            char[] managedArray = new char[4];
            // Initialize unmanged memory to hold the array.
            int size = sizeof(char) * 4;
            IntPtr pnt = Marshal.AllocHGlobal(size);

            try
            {

                ManagedMessenger._ReadMessageCharArray(_messengerId, pnt, capacity);
                // Copy the unmanaged array back to another managed array.
                for (int i = 0; i < 4; i++)
                    managedArray[i] = (char) Marshal.ReadInt16(pnt, i * sizeof(char));

            }
            finally
            {
                // Free the unmanaged memory.
                Marshal.FreeHGlobal(pnt);
            }
            return managedArray;
        }

        public static int[] ReadMessageIntArray(uint _messengerId)
        {
            int capacity = 32;
            // Create a managed array.
            int[] managedArray = new int[4];
            // Initialize unmanged memory to hold the array.
            int size = sizeof(int) * 4;
            IntPtr pnt = Marshal.AllocHGlobal(size);

            try
            {

                ManagedMessenger._ReadMessageIntArray(_messengerId, pnt, capacity);
                // Copy the unmanaged array back to another managed array.
                for (int i = 0; i < 4; i++)
                    managedArray[i] = (int) Marshal.ReadInt16(pnt, i * sizeof(int));

            }
            finally
            {
                // Free the unmanaged memory.
                Marshal.FreeHGlobal(pnt);
            }
            return managedArray;
        }

        public static message_t ReadMessageStruct(uint _messengerId)
        {
            int[] internalArray = new int[5];
            // Initialize unmanged memory to hold the array.
            int size = sizeof(int) + (sizeof(int) * 5);
            IntPtr pnt = Marshal.AllocHGlobal(size);
            message_t managedStruct;
            try
            {

                ManagedMessenger._ReadMessageStruct(_messengerId, pnt);

                int internalInt = Marshal.ReadInt32(pnt, 0);

                // Copy the unmanaged array back to another managed array.
                for (int i = 0; i < internalArray.Length; i++)
                    internalArray[i] = Marshal.ReadInt32(pnt, (i + 1) * 4);

                managedStruct.time = internalInt;
                managedStruct.test = internalArray;
            }
            finally
            {
                // Free the unmanaged memory.
                Marshal.FreeHGlobal(pnt);
            }
            return managedStruct;
        }

        private static IntPtr MarshalToPointer(message_t data)
        {
            IntPtr buf = Marshal.AllocHGlobal(Marshal.SizeOf(data));
            Marshal.StructureToPtr(data, buf, false);
            return buf;
        }
    }
}
