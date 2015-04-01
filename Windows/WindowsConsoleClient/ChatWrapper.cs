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
        const string dllPath = @"../../../NetworkCode/bin/NetworkCode.dll";

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        private extern static void init();

        public static void Init()
        {
            init();
        }

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        private extern static void readDebugBufferLine(int lineNum, StringBuilder lineBuffer, int bufferCapacity);

        public static string ReadDebugBufferLine(int lineNum, int capacity)
        {
            StringBuilder lineBuffer = new StringBuilder(capacity);
            readDebugBufferLine(lineNum, lineBuffer, lineBuffer.Capacity);
            return lineBuffer.ToString();
        }
        
        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        private extern static int getDebugBufferSize();

        public static int GetDebugBufferSize()
        {
            int size = getDebugBufferSize();
            return size;
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
