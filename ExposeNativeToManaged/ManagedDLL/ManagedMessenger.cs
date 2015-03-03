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

    [StructLayout(LayoutKind.Sequential)]
    public struct message_t2
    {
        public int time;
    }

    [StructLayout(LayoutKind.Sequential, CharSet=CharSet.Ansi)]
    public struct message_t3
    {
        public IntPtr message;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct message_t4
    {
        public int time;
        public IntPtr message;
    }

    [StructLayoutAttribute(LayoutKind.Sequential)]
    public struct message_s
    {

        /// int[4]
        [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 4)]
        public byte[] second;
    }

    public struct message_n
    {
        public int time;
        public int[] test;
    }

    public class ManagedMessenger : IDisposable
    {

        #region NativeDLL imports

        [DllImport("NativeDLL.dll", EntryPoint = "CreateMessenger", CallingConvention = CallingConvention.Cdecl)]
        protected static extern uint _CreateMessenger();

        [DllImport("NativeDLL.dll", EntryPoint = "DeleteMessenger", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void _DeleteMessenger(uint messengerId);

        [DllImport("NativeDLL.dll", EntryPoint = "WriteMessageInt", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void _WriteMessageInt(uint messengerId, uint message);

        [DllImport("NativeDLL.dll", EntryPoint = "WriteMessageString", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void _WriteMessageString(uint messengerId, String message);

        [DllImport("NativeDLL.dll", EntryPoint = "WriteMessageStruct", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void _WriteMessageStruct(uint messengerId, message_t message);

        [DllImport("NativeDLL.dll", EntryPoint = "ReadMessage", CallingConvention = CallingConvention.Cdecl)]
        protected static extern message_t _ReadMessage(uint messengerId);

        [DllImport("NativeDLL.dll", EntryPoint = "ReadMessage2", CallingConvention = CallingConvention.Cdecl)]
        protected static extern message_t2 _ReadMessage2(uint messengerId);

        [DllImport("NativeDLL.dll", EntryPoint = "ReadMessage3", CallingConvention = CallingConvention.Cdecl)]
        protected static extern message_t3 _ReadMessage3(uint messengerId);

        [DllImport("NativeDLL.dll", EntryPoint = "Test")]
        protected static extern message_s _Test();

        #endregion

        // Constructor
        public static uint CreateMessenger()
        {
            return _CreateMessenger();
        }

        public void Dispose()
        {

        }

        public static void DeleteMessenger(uint _messengerId)
        {
            _DeleteMessenger(_messengerId);
        }

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

        public static message_t ReadMessage(uint _messengerId)
        {
            return _ReadMessage(_messengerId);
        }

        public static message_t2 ReadMessage2(uint _messengerId)
        {
            return _ReadMessage2(_messengerId);
        }

        public static message_t3 ReadMessage3(uint _messengerId)
        {
            return _ReadMessage3(_messengerId);
        }

        public static message_s Test()
        {
            return _Test();
        }

        [DllImport("NativeDLL")]
        [return: MarshalAs(UnmanagedType.U4)]
        public static extern uint Dummy();



        [DllImport("NativeDLL", EntryPoint = "Dummy2",
                                CallingConvention = CallingConvention.Cdecl,
                                BestFitMapping = false,
                                CharSet = CharSet.Unicode,
                                ExactSpelling = true,
                                PreserveSig = true,
                                SetLastError = true,
                                ThrowOnUnmappableChar = false)]
        public static extern void Dummy2(IntPtr str, int capacity);

        [DllImport("NativeDLL", EntryPoint = "Dummy3",
                        CallingConvention = CallingConvention.Cdecl,
                        BestFitMapping = false,
                        CharSet = CharSet.Unicode,
                        ExactSpelling = true,
                        PreserveSig = true,
                        SetLastError = true,
                        ThrowOnUnmappableChar = false)]
        public static extern void Dummy3(IntPtr pnt, int capacity);

        [DllImport("NativeDLL", EntryPoint = "Dummy4",
                CallingConvention = CallingConvention.Cdecl,
                BestFitMapping = false,
                CharSet = CharSet.Unicode,
                ExactSpelling = true,
                PreserveSig = true,
                SetLastError = true,
                ThrowOnUnmappableChar = false)]
        public static extern IntPtr Dummy4();

        [DllImport("NativeDLL", EntryPoint = "Dummy5",
        CallingConvention = CallingConvention.Cdecl,
        BestFitMapping = false,
        CharSet = CharSet.Unicode,
        ExactSpelling = true,
        PreserveSig = true,
        SetLastError = true,
        ThrowOnUnmappableChar = false)]
        public static extern void Dummy5(IntPtr pnt, int capacity);

    }
}
