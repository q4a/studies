using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace KeepRes1 {
class Program {
    static void Main(string[] args) {
        Random random = new Random();
        List<int> listOfNumbers = new List<int>();
        int length = random.Next(50, 150);
        for (int i = 0; i < length; i++)
            listOfNumbers.Add(random.Next(100));    // [0, 100)

        Console.Write("Int list, length = {0}:", length);
        foreach (int v in listOfNumbers)
            Console.Write(" {0}", v);
        Console.WriteLine();

        var under50sorted =
            from number in listOfNumbers
            where number < 50
            orderby number descending
            select number;

        var firstFive = under50sorted.Take(5);
        List<int> shortList = firstFive.ToList();   // ToList 会立即计算结果
        Console.Write("Sorted (desc) short int list, length = {0}:", shortList.Count);
        foreach (int v in shortList)
            Console.Write(" {0}", v);

#if DEBUG
        Console.ReadKey();
#endif
    }
}
}
