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
            DebugWorker debugWorker = new DebugWorker();
            Thread debugThread = new Thread(debugWorker.DoWork);

            DebugPrint("Starting debug thread.");
            debugThread.Start();

            // Wait for the debug thread to start
            while(!debugThread.IsAlive);

            DebugPrint("Connecting to Google Hangout (0).");
            ChatWrapper.ConnectService(0);

            Thread.Sleep(60000);

            debugWorker.StopWorking();
            debugThread.Join();
            DebugPrint("Debug thread has terminated.");

            Console.Write("Press any key to exit...");
            Console.ReadKey();
        }

        static private void DebugPrint(string debugLine)
        {
            Console.WriteLine("Main thread> " + debugLine);
        }
    }
}
