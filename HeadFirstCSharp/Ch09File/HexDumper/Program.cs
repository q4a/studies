using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace HexDumper {
class Program {
    static void Main(string[] args) {
        if (args.Length != 1) {
            Console.Error.WriteLine("usage: hexdmper file-to-dump");
            Exit(1);
        }
        if (!File.Exists(args[0])) {
            Console.Error.WriteLine("File does not exist: {0}", args[0]);
            Exit(2);
        }
        // 不使用 StreamReader 包装，直接使用 Stream
        using (Stream input = File.OpenRead(args[0])) {
            int position = 0;
            byte[] buffer = new byte[16];
            while (position < input.Length) {
                int bytesRead = input.Read(buffer, 0, buffer.Length);
                if (bytesRead > 0) {
                    Console.Write("{0}: ", String.Format("{0:x4}", position));
                    position += bytesRead;
                    for (int i = 0; i < 16; i++) {
                        if (i < bytesRead) {
                            string hex = String.Format("{0:x2}", (byte) buffer[i]);
                            Console.Write(hex + " ");
                        }
                        else
                            Console.Write(" ");
                        if (i == 7)
                            Console.Write("-- ");
                        if (buffer[i] < 32 || buffer[i] > 127)
                            buffer[i] = (byte) '.';
                    }
                    // 以 UTF-8 编码将 byte 数组转换为字符串
                    string bufferContents = Encoding.UTF8.GetString(buffer);
                    Console.WriteLine(" " + bufferContents);
                }
            }
        }
        Exit(0);
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
