using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WindowsConsoleClient
{
    class MessageWorker
    {
        private const int buffer_size = 1024;

        private volatile bool isWorking;
        private uint nextMessage;

        public MessageWorker()
        {
            isWorking = true;
            nextMessage = 0;
        }

        public void DoWork()
        {
            while (isWorking)
            {
                if (ChatWrapper.GetNumMessages() > nextMessage)
                {
                    StringBuilder payloadBuffer = new StringBuilder(buffer_size);
                    int senderId = ChatWrapper.ReadMessage(nextMessage, ref payloadBuffer);
                    DebugPrint("Message from id:" + senderId + ">\"" + payloadBuffer.ToString() + "\"");
                    nextMessage++;
                }
            }
            DebugPrint("Exiting gracefully.");
        }

        public void StopWorking()
        {
            isWorking = false;
        }

        private void DebugPrint(string message)
        {
            Console.WriteLine("Message thread> " + message);
        }
    }
}
