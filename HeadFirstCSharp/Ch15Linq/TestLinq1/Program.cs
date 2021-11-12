using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace TestLinq1
{
    class Program
    {
        static void Main(string[] args)
        {
            int[] values = new int[] { 0, 12, 44, 36, 92, 54, 13, 8 };
            var result = from v in values
                         where v < 37
                         orderby v
                         select v;
            foreach (int i in result)
                Console.Write("{0} ", i);
            Console.ReadKey();
        }
    }
}
