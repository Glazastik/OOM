using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WPF_OOM
{
    class MessageWorker
    {
        private const int buffer_size = 4096;

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
                    Trace.WriteLine("MESSAGE RECIEVED");
                    StringBuilder payloadBuffer = new StringBuilder(buffer_size);
                    int senderId = ChatWrapper.ReadMessage(nextMessage, ref payloadBuffer);

                    foreach (Conversation c in MainWindow.conversations)
                    {
                        if (c.Person.GetId() == senderId)
                        {
                            int serviceId = ChatWrapper.GetServiceType(senderId);
                            App.Current.Dispatcher.Invoke((Action)delegate
                            {
                                c.AddMessage(new Message(payloadBuffer.ToString(), c.Person, new Account(serviceId, serviceId, "asd")));
                            });
                            
                        }
                    }

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
            Console.WriteLine("\nMessage thread> " + message + "\n");
        }
    }
}
