using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WindowsConsoleClient
{
    class DebugWorker
    {
        private volatile bool isWorking;

        public DebugWorker()
        {
            isWorking = true;
        }

        public void DoWork()
        {
            while (isWorking)
            {
                Console.WriteLine("Debug thread: doing work...");
            }
            Console.WriteLine("Debug thread: exiting gracefully.");
        }

        public void StopWorking()
        {
            isWorking = false;
        }
    }
}
