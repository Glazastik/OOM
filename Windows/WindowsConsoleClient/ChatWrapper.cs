﻿using System;
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
        private extern static void testConnect(int serviceType, StringBuilder buffer, int bufferCapacity);

        public static string TestConnect(int serviceType, int capacity)
        {
            StringBuilder buffer = new StringBuilder(capacity);
            testConnect(serviceType, buffer, buffer.Capacity);
            return buffer.ToString();
        }

        [DllImport("NetworkCode.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void getMessage(StringBuilder messageBuffer, int bufferCapacity);

        public static string GetMessage(int capacity)
        {
            StringBuilder messageBuffer = new StringBuilder(capacity);
            getMessage(messageBuffer, messageBuffer.Capacity);
            return messageBuffer.ToString();
        }

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
            return getDebugBufferSize();
        }
    }
}
