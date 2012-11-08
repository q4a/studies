using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace TestYield1
{
    class Program
    {
        static IEnumerable<string> NameEnumerator()
        {
            yield return "Bob"; // The method exits after this statement ...
            yield return "Harry"; // ... and resumes here the next time through
            yield return "Joe";
            yield return "Frank";
        }

        static void Main(string[] args)
        {
            IEnumerable<string> names = NameEnumerator(); // Put a breakpoint here
            foreach (string name in names)
                Console.WriteLine(name);
#if DEBUG
            Console.ReadKey();
#endif
        }
    }
}
