using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WindowsConsoleClient
{
    class DebugWorker
    {
        private const int buffer_size = 1024;

        private volatile bool isWorking;
        private int currentLine;

        public DebugWorker()
        {
            isWorking = true;
            currentLine = 0;
        }

        public void DoWork()
        {
            while (isWorking)
            {
                if (ChatWrapper.GetDebugBufferSize() > currentLine)
                {
                    DebugPrint(ChatWrapper.ReadDebugBufferLine(currentLine, buffer_size));
                    currentLine++;
                }
            }
            DebugPrint("Exiting gracefully.");
        }

        public void StopWorking()
        {
            isWorking = false;
        }

        private void DebugPrint(string debugLine)
        {
            Console.WriteLine("Debug thread>\n" + debugLine);
        }
    }
}
