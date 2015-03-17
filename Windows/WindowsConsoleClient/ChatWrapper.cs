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
        const string dllPath = @"NetworkCode.dll";

        [DllImport("NetworkCode.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void readDebugBufferLine(StringBuilder lineBuffer, int bufferCapacity);

        public static string ReadDebugBufferLine(int capacity)
        {
            StringBuilder lineBuffer = new StringBuilder(capacity);
            readDebugBufferLine(lineBuffer, lineBuffer.Capacity);
            return lineBuffer.ToString();
        }
        
        [DllImport("NetworkCode.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static int getDebugBufferSize();

        public static int GetDebugBufferSize()
        {
            Console.WriteLine("Before");
            return getDebugBufferSize();
            Console.WriteLine("After");
        }

        [DllImport("NetworkCode.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void connectService(int serviceType);

        public static void ConnectService(int serviceType)
        {
            connectService(serviceType);
        }

        [DllImport("NetworkCode.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void closeService(int serviceType);

        public static void CloseService(int serviceType)
        {
            closeService(serviceType);
        }
    }
}
