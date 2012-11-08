using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace Swindler
{
    class Program
    {
        const String FileDir = @"D:\source\cpp\study\StudyCSharp\Ch09File\data\";
        const String PlanFile = FileDir + @"secret_plan.txt";

        static void Main(string[] args)
        {
            StreamWriter sw = new StreamWriter(PlanFile);
            sw.WriteLine("How I'll defeat Captain Amazing");
            sw.WriteLine("Another genius secret plan by The Swindler");
            sw.Write("I'll create an army of clones and ");
            sw.WriteLine("unleash them upon the citizens of Objectville.");
            string location = "the mall";
            for (int number = 0; number <= 6; number++)
            {
                sw.WriteLine("Clone #{0} attacks {1}", number, location);
                if (location == "the mall") { location = "downtown"; }
                else { location = "the mall"; }
            }
            sw.Close();

            Console.Write("Press Any Key to Exit.");
            Console.ReadKey(true);
        }
    }
}
