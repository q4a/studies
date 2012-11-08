using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using HeadFirst.CSharp.Leftover2;
using HeadFirst.CppCLI.Leftover2;
using System.Windows.Forms;

namespace MyProgram1
{
    class Program
    {
        static void Main(string[] args)
        {
            Guy guy = new Guy("Joe", 43, 125);
            HiThereWriter.HiThere(guy.Name);
            HiThrereWriterCLI.HiThere(guy.Name);

            string str1 = "abcd汉字efgh";
            MessageBox.Show(String.Format("\"{0}\" length: {1}", str1, HiThrereWriterCLI.ComputeLength(str1)));
        }
    }
}
