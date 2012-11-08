// Program.cs
//
// SQL Server Compact 数据库 (.sdf) 的 LINQ 查询示例
//

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ContactDBLinq1 {
class Program {
    static void Main(string[] args) {
        string connectionString = "Data Source=|DataDirectory|\\ContactDB.sdf";
        // 用 SqlMetal 产生的 LINQ to SQL class
        // ContactDB 是 Linq.DataContext 的派生类
        ContactDB context = new ContactDB(connectionString);
        var peopleData =
            from person in context.People
            select new { person.Name, person.Company };
        foreach (var person in peopleData)
            Console.WriteLine("{0} works at {1}", person.Name, person.Company);

#if DEBUG
        Console.ReadKey();
#endif
    }
}

}
