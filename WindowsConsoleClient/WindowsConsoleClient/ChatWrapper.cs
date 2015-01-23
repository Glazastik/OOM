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
        [DllImport("NetworkCode.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void getMessage(StringBuilder messageBuffer, int bufferCapacity);

        public static string GetMessage(int capacity)
        {
            StringBuilder messageBuffer = new StringBuilder(capacity);
            getMessage(messageBuffer, messageBuffer.Capacity);
            return messageBuffer.ToString();
        }
    }
}
