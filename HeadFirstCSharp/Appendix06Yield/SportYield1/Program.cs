using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SportYield1
{
    enum Sport
    {
        Football, Baseball,
        Basketball, Hockey,
        Boxing, Rugby, Fencing,
    }

    class SportCollection : IEnumerable<Sport>
    {
        System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }
        public IEnumerator<Sport> GetEnumerator()
        {
            int maxEnumValue = Enum.GetValues(typeof(Sport)).Length - 1;
            for (int i = 0; i < maxEnumValue; i++)
            {
                yield return (Sport)i;
            }
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("SportCollection contents:");
            SportCollection sportCollection = new SportCollection();
            foreach (Sport sport in sportCollection)
                Console.WriteLine(sport.ToString());
#if DEBUG
            Console.ReadKey();
#endif
        }
    }
}
