using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ComicGroupPrice1 {
class Comic {
    public string Name {
        get;
        set;
    }
    public int Issue {
        get;
        set;
    }
}

class Program {

    private static IEnumerable<Comic> BuildCatalog() {
        return new List<Comic> {
            new Comic { Name = "Johnny America vs. the Pinko", Issue = 6 },
            new Comic { Name = "Rock and Roll (limited edition)", Issue = 19 },
            new Comic { Name = "Woman's Work", Issue = 36 },
            new Comic { Name = "Hippie Madness (misprinted)", Issue = 57 },
            new Comic { Name = "Revenge of the New Wave Freak (damaged)", Issue = 68 },
            new Comic { Name = "Black Monday", Issue = 74 },
            new Comic { Name = "Tribal Tattoo Madness", Issue = 83 },
            new Comic { Name = "The Death of an Object", Issue = 97 },
        };
    }

    private static Dictionary<int, decimal> GetPrices() {
        return new Dictionary<int, decimal> {
            { 6, 3600M },
            { 19, 500M },
            { 36, 650M },
            { 57, 13525M },
            { 68, 250M },
            { 74, 75M },
            { 83, 25.75M },
            { 97, 35.25M },
        };
    }

    enum PriceRange { Cheap, Midrange, Expensive }
    static PriceRange EvaluatePrice(decimal price) {
        if (price < 100M) return PriceRange.Cheap;
        else if (price < 1000M) return PriceRange.Midrange;
        else return PriceRange.Expensive;
    }

    static void Main(string[] args) {
        Dictionary<int, decimal> values = GetPrices();
        var priceGroups =
            from pair in values
            group pair.Key by EvaluatePrice(pair.Value)
            into priceGroup
            orderby priceGroup.Key descending
            select priceGroup;

        foreach (var group in priceGroups) {
            Console.Write("I found {0} {1} comics: issues ", group.Count(), group.Key);
            foreach (var price in group)
                Console.Write(price.ToString() + " ");
            Console.WriteLine();
        }

#if DEBUG
        Console.ReadKey();
#endif
    }
}

}
