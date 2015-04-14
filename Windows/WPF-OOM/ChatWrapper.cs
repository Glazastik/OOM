using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace WPF_OOM
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
        private extern static void stop();

        public static void Stop()
        {
            stop();
        }

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        private extern static void connectService(int serviceType);

        public static void ConnectService(int serviceType)
        {
            connectService(serviceType);
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
        private extern static void addPerson(int id, string name);

        public static void AddPerson(Person person)
        {
            addPerson(person.GetId(), person.GetName());
        }

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        private extern static void addAccountToPerson(int personId, int accountId, int serviceType, string address);

        public static void AddAccountToPerson(int personId, Account account)
        {
            addAccountToPerson(personId, account.GetId(), account.GetServiceType(), account.GetAddress());
        }

        [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        private extern static void sendChatMessage(int accountId, string message);

        public static void SendChatMessage(int accountId, string message)
        {
            sendChatMessage(accountId, message);
        }
            [DllImport(dllPath, CallingConvention = CallingConvention.Cdecl)]
        private extern static int getServiceType(int accountId);

        public static int GetServiceType(int accountId)
        {
            return getServiceType(accountId);
        }
    }
}
