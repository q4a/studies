using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ModifyResult1 {
class Program {
    static void Main(string[] args) {
        string[] sandwiches = { "ham and cheese", "salami with mayo",
                                "turkey and swiss", "chicken cutlet"
                              };
        var sandwichesOnRye =
            from sandwich in sandwiches
            select sandwich + " on rye";
        foreach (var sandwich in sandwichesOnRye)
            Console.WriteLine(sandwich);
#if DEBUG
        Console.ReadKey();
#endif
    }
}
}
