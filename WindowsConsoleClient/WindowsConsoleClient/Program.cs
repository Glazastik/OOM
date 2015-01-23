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
            Console.WriteLine(ChatWrapper.GetMessage(512));

            Console.Write("Press any key to exit...");
            Console.ReadKey();
        }
    }
}
