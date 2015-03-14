using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WindowsConsoleClient
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine(ChatWrapper.GetMessage(1024));
            Console.WriteLine(ChatWrapper.TestConnect(0, 1025));

            // Dll debug test
            Console.WriteLine("Dll debug test: " + ChatWrapper.ReadDebugBufferLine(1024));

            Console.Write("Press any key to exit...");
            Console.ReadKey();
        }
    }
}
