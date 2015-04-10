using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;


namespace WindowsConsoleClient
{
    class Program
    {
        static void Main(string[] args)
        {
            ChatWrapper.Init();

            // Thread test
            MessageWorker messageWorker = new MessageWorker();
            Thread messageThread = new Thread(messageWorker.DoWork);

            DebugPrint("Starting message thread.");
            messageThread.Start();

            // Wait for the debug thread to start
            while(!messageThread.IsAlive);

            DebugPrint("Connecting to Google Hangout (0).");
            ChatWrapper.ConnectService(0);

            Thread.Sleep(60000);

            messageWorker.StopWorking();
            messageThread.Join();
            DebugPrint("Message thread has terminated.");

            Console.Write("Press any key to exit...");
            Console.ReadKey();
        }

        static private void DebugPrint(string debugLine)
        {
            Console.WriteLine("Main thread> " + debugLine);
        }
    }
}
