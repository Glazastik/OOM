using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace ManagedDLL
{
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct message_t
    {
        public int time;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 5, ArraySubType = UnmanagedType.I4)]
        public int[] test;
    }
        
    public class ManagedMessenger
    {

        #region NativeDLL imports

        //
        // Creating a messenger with ID
        //
        [DllImport("NativeDLL.dll", EntryPoint = "CreateMessenger", CallingConvention = CallingConvention.Cdecl)]
        protected static extern uint _CreateMessenger();

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
        // Other functions
        //
        [DllImport("NativeDLL", EntryPoint = "HasMessage", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool _HasMessage();

        [DllImport("NativeDLL", EntryPoint = "CallingBack", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool _CallingBack(IntPtr p);

        #endregion

        // Creating Messenger
        public static uint CreateMessenger()
        {
            return _CreateMessenger();
        }

        public static void DeleteMessenger(uint _messengerId)
        {
            _DeleteMessenger(_messengerId);
        }

        //
        // Writing data
        //
        public static void WriteMessageInt(uint _messengerId, uint message)
        {
            _WriteMessageInt(_messengerId, message);
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
            IntPtr buf = Marshal.AllocHGlobal(
                Marshal.SizeOf(data));
            Marshal.StructureToPtr(data,
                buf, false);
            return buf;
        }
    }
}
