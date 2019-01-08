郑州大学 汇编语言程序设计
https://www.icourse163.org/course/ZZU-1001796025
授课老师 郑州大学 钱晓捷 [副教授] 张青 [讲师]

示例练习代码

----------
使用 NMake 管理并构建工程
https://docs.microsoft.com/en-us/cpp/build/nmake-reference

nmake /nologo                   默认使用 Debug 配置构建
nmake /nologo config=Release    使用 Release 配置构建
nmake /nologo clean             清理 Debug 配置时生成的中间文件和结果文件

----------
C/C++-Assembly 混合编程示例工程

C8_3_Module
需要 VS 6.0 的 MSVC 6.0 C/C++ 编译器和相关 MSVCRT, Windows API 头文件、库文件

注意：
Microsoft 官方的 VS 6.0 + SP6 + VC 6.0 Processor Pack (MASM 6.15.8803) 不包含课程教学的 I/O 子程序库 io16.inc/.lib, io32.inc/.lib
如果使用 io16.inc/.lib, io32.inc/.lib，需要自行拷贝或设置路径

其它示例只需 MASM 6 开发包
