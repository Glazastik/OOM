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
            Console.WriteLine("Connecting to Google Hangout.");
            ChatWrapper.ConnectService(1337);
            //Console.WriteLine(ChatWrapper.GetDebugBufferSize());
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
