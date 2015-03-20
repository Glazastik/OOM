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
            Console.WriteLine("Connecting to Google Hangout.");
            //ChatWrapper.ConnectService(1337);
            Console.WriteLine(ChatWrapper.GetDebugBufferSize());
            Console.WriteLine("After");

            // Thread test
            DebugWorker debugWorker = new DebugWorker();
            Thread debugThread = new Thread(debugWorker.DoWork);

            debugThread.Start();
            Console.WriteLine("main thread: Starting debug thread.");

            while(!debugThread.IsAlive);

            Thread.Sleep(5);

            debugWorker.StopWorking();
            debugThread.Join();
            Console.WriteLine("main thread: Debug thread has terminated.");

            /*
            while (ChatWrapper.GetDebugBufferSize() > 0)
            {
                Console.WriteLine("NetworkCode>" + ChatWrapper.ReadDebugBufferLine(1024));
            }
            */

            Console.Write("Press any key to exit...");
            Console.ReadKey();
        }
    }
}
