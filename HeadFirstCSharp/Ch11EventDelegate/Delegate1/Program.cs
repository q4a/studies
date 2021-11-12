using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Delegate1 {

delegate string ConvertsIntToString(int i);

class Program {

    static void Main(string[] args) {
        ConvertsIntToString someMethod = new ConvertsIntToString(HiThere);
        string message = someMethod(5);
        Console.WriteLine(message);
        Exit(0);
    }

    private static string HiThere(int i) {
        return "Hi there! #" + (i * 100);
    }

    static void Exit(int exitCode) {
#if DEBUG
        Console.Write("Press Any Key to Exit.");
        Console.ReadKey(true);
        System.Environment.Exit(exitCode);  // 结束程序，类似 CRT 的 exit 函数
#endif
    }
}

}
