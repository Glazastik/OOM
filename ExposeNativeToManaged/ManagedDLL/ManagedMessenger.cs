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

    public struct LoginData
    {
        public String userName;
        public String password;
    }

    // this is the way, with malloc and copy
    // the same to do with contacts
    public struct internal_login
    {
        public int userNameSize;
        public IntPtr userName;
        public int passwordSize;
        public IntPtr password;
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
        [DllImport("NativeDLL", EntryPoint = "SendMessageMessenger", CallingConvention = CallingConvention.Cdecl)]
        public static extern void _SendMessageMessenger(uint messenger);

        [DllImport("NativeDLL", EntryPoint = "SendMessageData", CallingConvention = CallingConvention.Cdecl)]
        public static extern void _SendMessageData(IntPtr data, int size);

        /*
         * Old version of _SendMessageData
         * 
        [DllImport("NativeDLL", EntryPoint = "SendMessageData", CallingConvention = CallingConvention.Cdecl)]
        public static extern void _SendMessageData([MarshalAs(UnmanagedType.BStr)] String data, int length);*/

        [DllImport("NativeDLL", EntryPoint = "SendMessageContact", CallingConvention = CallingConvention.Cdecl)]
        public static extern void _SendMessageContact(IntPtr contact);

        [DllImport("NativeDLL", EntryPoint = "SendMessageContactName", CallingConvention = CallingConvention.Cdecl)]
        public static extern void _SendMessageContactName(IntPtr name, int length);

        [DllImport("NativeDLL", EntryPoint = "_SendMessage", CallingConvention = CallingConvention.Cdecl)]
        public static extern void _SendMessage();

        //
        // Getting messages
        //
        [DllImport("NativeDLL", EntryPoint = "_GetMessage", CallingConvention = CallingConvention.Cdecl)]
        public static extern void _GetMessage();

        [DllImport("NativeDLL", EntryPoint = "GetMessageMessenger", CallingConvention = CallingConvention.Cdecl)]
        public static extern uint _GetMessageMessenger();

        [DllImport("NativeDLL", EntryPoint = "GetMessageSize", CallingConvention = CallingConvention.Cdecl)]
        public static extern uint _GetMessageSize();

        [DllImport("NativeDLL", EntryPoint = "GetMessageData", CallingConvention = CallingConvention.Cdecl)]
        public static extern void _GetMessageData(IntPtr data);

        [DllImport("NativeDLL", EntryPoint = "GetMessageContactNameSize", CallingConvention = CallingConvention.Cdecl)]
        public static extern uint _GetMessageContactNameSize();

        [DllImport("NativeDLL", EntryPoint = "GetMessageContact", CallingConvention = CallingConvention.Cdecl)]
        public static extern void _GetMessageContact(IntPtr contact);

        [DllImport("NativeDLL", EntryPoint = "GetMessageContactName", CallingConvention = CallingConvention.Cdecl)]
        public static extern void _GetMessageContactName(IntPtr contactName);


        //
        // Other functions
        //
        [DllImport("NativeDLL", EntryPoint = "Initiliaze", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool _Initiliaze();

        [DllImport("NativeDLL", EntryPoint = "HasMessage", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool _HasMessage();

        [DllImport("NativeDLL", EntryPoint = "CallingBack", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool _CallingBack(IntPtr p);


        //
        // Login
        //
        [DllImport("NativeDLL", EntryPoint = "Login", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool _Login(uint messenger, IntPtr loginData);

        [DllImport("NativeDLL", EntryPoint = "GetLogin", CallingConvention = CallingConvention.Cdecl)]
        public static extern void _GetSizeUserName();

        [DllImport("NativeDLL", EntryPoint = "GetLogin", CallingConvention = CallingConvention.Cdecl)]
        public static extern void _GetSizePassword();

        [DllImport("NativeDLL", EntryPoint = "GetLogin", CallingConvention = CallingConvention.Cdecl)]
        public static extern void _GetLogin(IntPtr loginData);

        #endregion

        private Messenger[] messengers;

        //
        // Creating Messenger
        //
        public ManagedMessenger()
        {
            _Initiliaze();
            messengers = new Messenger[3];
        }

        public void AddMessenger(Messenger messenger)
        {
            _AddMessenger((uint)messenger); 
        }

        public void DeleteMessenger(Messenger messenger)
        {
            _DeleteMessenger((uint)messenger);
        }

        //
        // Login
        //
        public bool Login(Messenger messenger, LoginData login)
        {
            return LoginAllocator((uint)messenger, login);
        }

        // This approach or contact approach
        private bool LoginAllocator(uint messenger, LoginData login)
        {
            // Initialize unmanged memory to hold the array.
            char[] internalUserName = login.userName.ToCharArray();
            char[] internalPassword = login.password.ToCharArray();

            IntPtr userName = Marshal.AllocHGlobal(sizeof(char) * internalUserName.Length);
            IntPtr password = Marshal.AllocHGlobal(sizeof(char) * internalPassword.Length);

            IntPtr pnt = Marshal.AllocHGlobal(sizeof(int) + sizeof(int) + sizeof(int) + sizeof(int));

            try
            {
                // Copy the managed array to unmanaged memory.
                Marshal.Copy(internalUserName, 0, userName, internalUserName.Length);
                Marshal.Copy(internalPassword, 0, password, internalPassword.Length);

                Marshal.WriteInt32(pnt, sizeof(int) * 0, internalUserName.Length);
                Marshal.WriteIntPtr(pnt, sizeof(int) * 1, userName);
                Marshal.WriteInt32(pnt, sizeof(int) * 2, internalPassword.Length);
                Marshal.WriteIntPtr(pnt, sizeof(int) * 3, password);
                return _Login(messenger, pnt);
            }
            finally
            {
                // Free the unmanaged memory.
                Marshal.FreeHGlobal(userName);
                Marshal.FreeHGlobal(password);
                Marshal.FreeHGlobal(pnt);
            }
        }

        //
        // Has message?
        //
        public bool HasMessage()
        {
            return _HasMessage();
        }

        //
        // Send message
        //
        public void SendMessage(Message message)
        {
            SendMessageMessenger(message.messenger);
            SendMessageData(message.message.ToCharArray());
            SendMessageContact(message.contact);
            _SendMessage();
        }

        private void SendMessageMessenger(Messenger messenger)
        {
            _SendMessageMessenger((uint)messenger);
        }

        private void SendMessageData(char[] data)
        {
            // Initialize unmanged memory to hold the array.
            SendCharData(new SendData(ManagedMessenger._SendMessageData),
                                        CharDataAllocator(data.Length), data);
        }

        private void SendMessageData2(char[] data)
        {
            // Initialize unmanged memory to hold the array.
            int size = (sizeof(char) * data.Length);
            IntPtr pnt = Marshal.AllocHGlobal(size);
            try
            {
                // Copy the managed array to unmanaged memory.
                Marshal.Copy(data, 0, pnt, data.Length);
                ManagedMessenger._SendMessageData(pnt, data.Length);
            }
            finally
            {
                // Free the unmanaged memory.
                Marshal.FreeHGlobal(pnt);
            }
        }

        private void SendMessageContact(Contact contact)
        {
            // Initialize unmanged memory to hold the array.
            char[] name = contact.name.ToCharArray();
            IntPtr internalName = CharDataAllocator(name.Length);
            SendCharData(new SendData(ManagedMessenger._SendMessageContactName), internalName, name);

            IntPtr pnt = Marshal.AllocHGlobal(sizeof(int) + sizeof(int) + sizeof(int));

            try
            {
                // Copy the managed array to unmanaged memory.
                Marshal.WriteInt32(pnt, sizeof(int) * 0, contact.id);
                Marshal.WriteInt32(pnt, sizeof(int) * 1, name.Length);
                Marshal.WriteIntPtr(pnt, sizeof(int) * 2, (IntPtr)0);   // Dummy null-pointer
                ManagedMessenger._SendMessageContact(pnt);
            }
            finally
            {
                // Free the unmanaged memory.
                Marshal.FreeHGlobal(pnt);
            }
        }

        private internal_contact toInternalContact(Contact contact)
        {
            internal_contact temp;
            temp.id = contact.id;
            temp.length = contact.name.Length;
            temp.name = new char[256];
            char[] name = contact.name.ToCharArray();
            for (int i = 0; i < name.Length; i++ )
            {
                temp.name[i] = name[i];
            }
            return temp;
        }

        //
        // Get message
        //
        public Message GetMessage()
        {
            _GetMessage();

            Message message;
            message.messenger = GetMessageMessenger();
            message.contact = GetMessageContact(); 
            message.message = GetMessageString();
                
            return message;
        }

        private String GetMessageString()
        {
            return new String(GetMessageData((int)_GetMessageSize()));
        }

        private Messenger GetMessageMessenger()
        {
            return (Messenger)_GetMessageMessenger();
        }

        private IntPtr ByteDataAllocator(int capacity)
        {
            int size = (sizeof(byte) * capacity);
            IntPtr pnt = Marshal.AllocHGlobal(size);
            return pnt;
        }

        private IntPtr CharDataAllocator(int capacity)
        {
            int size = (sizeof(char) * capacity);
            IntPtr pnt = Marshal.AllocHGlobal(size);
            return pnt;
        }

        private IntPtr IntDataAllocator(int capacity)
        {
            int size = (sizeof(int) * capacity);
            IntPtr pnt = Marshal.AllocHGlobal(size);
            return pnt;
        }

        private delegate void GetData(IntPtr pnt);
        private delegate void SendData(IntPtr pnt, int length);

        private void SendCharData(SendData sendData, IntPtr pnt, char[] data)
        {
            // Initialize unmanged memory to hold the array.
            try
            {
                // Copy the managed array to unmanaged memory.
                Marshal.Copy(data, 0, pnt, data.Length);
                sendData(pnt, data.Length);
            }
            finally
            {
                // Free the unmanaged memory.
                Marshal.FreeHGlobal(pnt);
            }
        }

        private char[] GetCharData(GetData getData, IntPtr pnt, int capacity)
        {
            char[] data = new char[capacity];

            try
            {
                // Call the get data function in unmanaged code.
                getData(pnt);
                // Copy the unmanaged array back to another managed array.
                for (int i = 0; i < data.Length; i++)
                {
                    data[i] = (char)Marshal.ReadInt16(pnt, i * sizeof(char));
                }
            }
            finally
            {
                // Free the unmanaged memory.
                Marshal.FreeHGlobal(pnt);
            }
            return data;
        }

        private char[] GetMessageData(int capacity)
        {
            return GetCharData(new GetData(ManagedMessenger._GetMessageData), CharDataAllocator(capacity), capacity); 
        }

        private Contact GetMessageContact()
        {
            // Initialize unmanged memory to hold the array.
            
            IntPtr pnt = IntDataAllocator(3);
            IntPtr internalName = CharDataAllocator((int)_GetMessageContactNameSize());
            Contact contact;
            try
            {
                // Set the pointer to chars
                Marshal.WriteIntPtr(pnt, sizeof(int) * 2, internalName);   //behövs ej
                ManagedMessenger._GetMessageContact(pnt);
                contact.id = Marshal.ReadInt32(pnt, 0);
                contact.name = new String(GetCharData(
                                    new GetData(ManagedMessenger._GetMessageContactName), 
                                                internalName, 
                                                  (int)_GetMessageContactNameSize()));
            }
            finally
            {
                // Free the unmanaged memory.
                Marshal.FreeHGlobal(pnt);
            }
            return contact;
        }

        private Contact toContact(internal_contact contact)
        {
            Contact temp;
            temp.id = contact.id;
            temp.name = new String(contact.name, 0, contact.length);
            return temp;
        }



         /*



        private Contact ReadMessageContact()
        {
            // Initialize unmanged memory to hold the array.
            char[] name = new char[_GetMessageContactSize()];
            IntPtr internalName = Marshal.AllocHGlobal(sizeof(char) * name.Length);
            IntPtr pnt = Marshal.AllocHGlobal(sizeof(int) + sizeof(int) + sizeof(int));

            Contact managedStruct;
            try
            {
                // Set the pointer to chars
                Marshal.WriteIntPtr(pnt, sizeof(int) * 2, internalName);
                ManagedMessenger._GetMessageContact(pnt);


                managedStruct.id = Marshal.ReadInt32(pnt, 0);
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
        }*/




        /*

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
        } */

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
