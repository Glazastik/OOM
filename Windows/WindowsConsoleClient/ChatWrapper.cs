using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace WindowsConsoleClient
{
    class ChatWrapper
    {
        const string dllPath = @"../../../NetworkCode/bin/NetworkCode.dll";

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        private extern static void init();

        public static void Init()
        {
            init();
        }

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        private extern static int readMessage(uint messageNum, StringBuilder messageBuffer, int bufferCapacity);

        public static int ReadMessage(uint messageNum, ref StringBuilder payloadBuffer)
        {
            int senderId = readMessage(messageNum, payloadBuffer, payloadBuffer.Capacity);
            return senderId;
        }

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        private extern static int getNumMessages();

        public static int GetNumMessages()
        {
            int numMessages = getNumMessages();
            return numMessages;
        }

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        private extern static void connectService(int serviceType);

        public static void ConnectService(int serviceType)
        {
            connectService(serviceType);
        }

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        private extern static void closeService(int serviceType);

        public static void CloseService(int serviceType)
        {
            closeService(serviceType);
        }
    }
}
