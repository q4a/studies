using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace ReadSwindler
{
    class Program
    {
        const String FileDir = @"D:\source\cpp\study\StudyCSharp\Ch09File\data\";
        const String PlanFile = FileDir + @"secret_plan.txt";
        const String MailFile = FileDir + @"emailToCaptainAmazing.txt";

        static void Main(string[] args)
        {
            StreamReader reader = new StreamReader(PlanFile);
            StreamWriter writer = new StreamWriter(MailFile);

            writer.WriteLine("To: CaptainAmazing@objectville.net");
            writer.WriteLine("From: Commissioner@objectiville.net");
            writer.WriteLine("Subject: Can you save the day... again?");
            writer.WriteLine();
            writer.WriteLine("We've discovered the Swindler's plan:");
            while (!reader.EndOfStream)
            {
                string lineFromThePlan = reader.ReadLine();
                writer.WriteLine("The plan -> " + lineFromThePlan);
            }
            writer.WriteLine();
            writer.WriteLine("Can you help us?");
            writer.Close();
            reader.Close();

            Console.Write("Press Any Key to Exit.");
            Console.ReadKey(true);
        }
    }
}
