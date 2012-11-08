using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LinqCalc1 {
class Program {
    static void Main(string[] args) {
        Random random = new Random();
        List<int> listOfNumbers = new List<int>();
        int length = random.Next(50, 150);
        for (int i = 0; i < length; i++)
            listOfNumbers.Add(random.Next(100));    // [0, 100)

        Console.Write("Int list, length = {0}:", length);
        // int v 可用 var v 代替，让编译器推导类型，类似 C++11 的 auto
        foreach (var v in listOfNumbers)
            Console.Write(" {0}", v);
        Console.WriteLine();

        Console.WriteLine("There are {0} numbers",
                          listOfNumbers.Count());
        Console.WriteLine("The smallest is {0}",
                          listOfNumbers.Min());
        Console.WriteLine("The biggest is {0}",
                          listOfNumbers.Max());
        Console.WriteLine("The sum is {0}",
                          listOfNumbers.Sum());
        Console.WriteLine("The average is {0:F2}",
                          listOfNumbers.Average());
#if DEBUG
        Console.ReadKey();
#endif
    }
}
}
