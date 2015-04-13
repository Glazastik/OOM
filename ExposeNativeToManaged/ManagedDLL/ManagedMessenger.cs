using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace ManagedDLL
{
    public enum Messenger
    {
        irc = 0,
        google = 1,
        facebook = 2
    };

    #region structures

    /*
     *   DETTA SÄTTET FUNKAR EJ
     * 
     * [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
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
    }                   */

    public struct Contact
    {
        public String id;
        public String name;
    }

    public struct Message
    {
        public String data;
        public String cid;
    }

    public struct LoginData
    {
        public String userName;
        public String password;
    }

    #endregion

    public class ManagedMessenger
    {
        #region NativeDLL imports

        //
        // Initialize
        //
        [DllImport("NativeDLL", EntryPoint = "Initiliaze", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool _Initiliaze();

        [DllImport("NativeDLL.dll", EntryPoint = "DeleteMessenger", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void _DeleteMessenger();

        //
        // Login
        //
        [DllImport("NativeDLL", EntryPoint = "Login", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool _Login(Messenger messenger, IntPtr loginData);

        //
        // Sending messages
        //
        [DllImport("NativeDLL", EntryPoint = "SendMessageData", CallingConvention = CallingConvention.Cdecl)]
        public static extern void _SendMessageData(IntPtr data, int size);

        [DllImport("NativeDLL", EntryPoint = "SendMessageCid", CallingConvention = CallingConvention.Cdecl)]
        public static extern void _SendMessageCid(IntPtr name, int length);

        /*
         * Old version of _SendMessageData
         * 
        [DllImport("NativeDLL", EntryPoint = "SendMessageData", CallingConvention = CallingConvention.Cdecl)]
        public static extern void _SendMessageData([MarshalAs(UnmanagedType.BStr)] String data, int length);*/

        [DllImport("NativeDLL", EntryPoint = "_SendMessage", CallingConvention = CallingConvention.Cdecl)]
        public static extern void _SendMessage(Messenger messenger);

        //
        // Getting messages
        //
        [DllImport("NativeDLL", EntryPoint = "HasMessage", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool _HasMessage(Messenger messenger);

        [DllImport("NativeDLL", EntryPoint = "_GetMessage", CallingConvention = CallingConvention.Cdecl)]
        public static extern void _GetMessage(Messenger messenger);

        [DllImport("NativeDLL", EntryPoint = "GetMessageDataSize", CallingConvention = CallingConvention.Cdecl)]
        public static extern int _GetMessageDataSize();

        [DllImport("NativeDLL", EntryPoint = "GetMessageData", CallingConvention = CallingConvention.Cdecl)]
        public static extern void _GetMessageData(IntPtr data);

        [DllImport("NativeDLL", EntryPoint = "GetMessageCidSize", CallingConvention = CallingConvention.Cdecl)]
        public static extern int _GetMessageCidSize();

        [DllImport("NativeDLL", EntryPoint = "GetMessageCid", CallingConvention = CallingConvention.Cdecl)]
        public static extern void _GetMessageCid(IntPtr cid);

        //
        // Get contacts
        //
        [DllImport("NativeDLL", EntryPoint = "GetContacts", CallingConvention = CallingConvention.Cdecl)]
        public static extern void _GetContacts(Messenger messenger);

        [DllImport("NativeDLL", EntryPoint = "HasContact", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool _HasContact(Messenger messenger);

        [DllImport("NativeDLL", EntryPoint = "GetContact", CallingConvention = CallingConvention.Cdecl)]
        public static extern void _GetContact(Messenger messenger);

        [DllImport("NativeDLL", EntryPoint = "GetContactIdSize", CallingConvention = CallingConvention.Cdecl)]
        public static extern int _GetContactIdSize();

        [DllImport("NativeDLL", EntryPoint = "GetContactId", CallingConvention = CallingConvention.Cdecl)]
        public static extern void _GetContactId(IntPtr id);

        [DllImport("NativeDLL", EntryPoint = "GetContactNameSize", CallingConvention = CallingConvention.Cdecl)]
        public static extern int _GetContactNameSize();

        [DllImport("NativeDLL", EntryPoint = "GetContactName", CallingConvention = CallingConvention.Cdecl)]
        public static extern void _GetContactName(IntPtr name);
        
        //
        // Other functions
        //
        [DllImport("NativeDLL", EntryPoint = "CallingBack", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool _CallingBack(IntPtr pnt);

        #endregion

        private Messenger[] messengers;

        //
        // Creating/Deleting Messenger
        //
        public ManagedMessenger()
        {
            _Initiliaze();
            messengers = new Messenger[3];
        }

        public void DeleteMessenger()
        {
            _DeleteMessenger();
        }

        //
        // Login
        //
        public bool Login(Messenger messenger, LoginData login)
        {
            return LoginAllocator(messenger, login);
        }

        // This approach or message approach
        private bool LoginAllocator(Messenger messenger, LoginData login)
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
        // Send message
        //
        public void SendMessage(Messenger messenger, Message message)
        {
            SendMessageData(message.data.ToCharArray());
            SendMessageCid(message.cid.ToCharArray());
            _SendMessage(messenger);
        }

        private void SendMessageData(char[] data)
        {
            SendCharData(new SendData(ManagedMessenger._SendMessageData),
                                        CharDataAllocator(data.Length), data);
        }

        private void SendMessageCid(char[] cid)
        {
            SendCharData(new SendData(ManagedMessenger._SendMessageCid),
                                        CharDataAllocator(cid.Length), cid);
        }

        //
        // Has message?
        //
        public bool HasMessage(Messenger messenger)
        {
            return _HasMessage(messenger);
        }

        //
        // Get message
        //
        public Message GetMessage(Messenger messenger)
        {
            _GetMessage(messenger);

            Message message;
            message.data = GetMessageData();
            message.cid = GetMessageCid(); 
        
            return message;
        }

        private String GetMessageData()
        {
            return new String(GetMessageData(_GetMessageDataSize()));
        }

        private char[] GetMessageData(int capacity)
        {
            return GetCharData(new GetData(ManagedMessenger._GetMessageData),
                                                    CharDataAllocator(capacity), capacity);
        }

        private String GetMessageCid()
        {
            return new String(GetMessageCid(_GetMessageCidSize()));
        }

        private char[] GetMessageCid(int capacity)
        {
            return GetCharData(new GetData(ManagedMessenger._GetMessageCid),
                                                    CharDataAllocator(capacity), capacity);
        }

        //
        // Get Contacts
        //
        public List<Contact> GetContacts(Messenger messenger)
        {
            _GetContacts(messenger);
            List<Contact> contacts = new List<Contact>();
            while(_HasContact(messenger))
            {
                contacts.Add(GetContact(messenger));
            }
            return contacts;
        }

        private Contact GetContact(Messenger messenger)
        {
            _GetContact(messenger);

            Contact contact;

            contact.id = GetContactId();
            contact.name = GetContactName();

            return contact;
        }

        private String GetContactId()
        {
            return new String(GetContactId(_GetContactIdSize()));
        }

        private char[] GetContactId(int capacity)
        {
            return GetCharData(new GetData(ManagedMessenger._GetContactId),
                                                    CharDataAllocator(capacity), capacity);
        }

        private String GetContactName()
        {
            return new String(GetContactName(_GetContactNameSize()));
        }

        private char[] GetContactName(int capacity)
        {
            return GetCharData(new GetData(ManagedMessenger._GetContactName),
                                                    CharDataAllocator(capacity), capacity);
        }

        //
        // Allocators and GET/SEND
        //
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

        // Get and Send, DLL functions
        private delegate void GetData(IntPtr pnt);
        private delegate void SendData(IntPtr pnt, int length);

        private void SendByteData(SendData sendData, IntPtr pnt, byte[] data)
        {
            try
            {
                // Copy the managed array to unmanaged memory.
                Marshal.Copy(data, 0, pnt, data.Length);
                // Call the send data function in unmanaged code.
                sendData(pnt, data.Length);
            }
            finally
            {
                // Free the unmanaged memory.
                Marshal.FreeHGlobal(pnt);
            }
        }

        private void SendCharData(SendData sendData, IntPtr pnt, char[] data)
        {
            try
            {
                // Copy the managed array to unmanaged memory.
                Marshal.Copy(data, 0, pnt, data.Length);
                // Call the send data function in unmanaged code.
                sendData(pnt, data.Length);
            }
            finally
            {
                // Free the unmanaged memory.
                Marshal.FreeHGlobal(pnt);
            }
        }

        private void SendIntData(SendData sendData, IntPtr pnt, int[] data)
        {
            try
            {
                // Copy the managed array to unmanaged memory.
                Marshal.Copy(data, 0, pnt, data.Length);
                // Call the send data function in unmanaged code.
                sendData(pnt, data.Length);
            }
            finally
            {
                // Free the unmanaged memory.
                Marshal.FreeHGlobal(pnt);
            }
        }

        private byte[] GetByteData(GetData getData, IntPtr pnt, int capacity)
        {
            byte[] data = new byte[capacity];

            try
            {
                // Call the get data function in unmanaged code.
                getData(pnt);
                // Copy the unmanaged array back to managed array.
                for (int i = 0; i < data.Length; i++)
                {
                    data[i] = (byte)Marshal.ReadByte(pnt, i * sizeof(byte));
                }
            }
            finally
            {
                // Free the unmanaged memory.
                Marshal.FreeHGlobal(pnt);
            }
            return data;
        }

        private char[] GetCharData(GetData getData, IntPtr pnt, int capacity)
        {
            char[] data = new char[capacity];

            try
            {
                // Call the get data function in unmanaged code.
                getData(pnt);
                // Copy the unmanaged array back to managed array.
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

        private int[] GetIntData(GetData getData, IntPtr pnt, int capacity)
        {
            int[] data = new int[capacity];

            try
            {
                // Call the get data function in unmanaged code.
                getData(pnt);
                // Copy the unmanaged array back to managed array.
                for (int i = 0; i < data.Length; i++)
                {
                    data[i] = (int)Marshal.ReadInt32(pnt, i * sizeof(int));
                }
            }
            finally
            {
                // Free the unmanaged memory.
                Marshal.FreeHGlobal(pnt);
            }
            return data;
        }

    }
}
