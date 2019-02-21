[郑州大学 汇编语言程序设计](https://www.icourse163.org/course/ZZU-1001796025) 示例练习代码  
授课老师 郑州大学 钱晓捷 张青

示例工程使用 [NMake](https://docs.microsoft.com/en-us/cpp/build/nmake-reference) 管理构建

    nmake /nologo                   # 默认使用 Debug 配置构建
    nmake /nologo config=Release    # 使用 Release 配置构建
    nmake /nologo clean             # 清理 Debug 配置时生成的中间文件和结果文件

# 示例工程说明

**C8_3_Module**  
C/C++-Assembly 混合编程工程  
需要 VC 6.0 C/C++ 编译工具链（含 MASM 6 汇编器）和 MSVCRT 及 Windows API .h/.lib  
不依赖课程教学的 I/O 子程序库

Microsoft Visual Studio 6.0.zip [[百度网盘 提取码 zwld](https://pan.baidu.com/s/1z_Ds4yGsOlzJ8OIuLaQDVA)] 由以下开发包整合而得：
1. VS 6.0 Enterprise (only VC 6.0 part)
2. VS 6.0 SP 6
3. VC 6.0 Processor Pack (MASM 6.15.8803)

**除 C8_3_Module 之外的其它示例**  
依赖课程教学的 MASM 6 QXJ 开发包 [[百度网盘 提取码 pxck](https://pan.baidu.com/s/1tQoRc_Q_qd1p2w2NfldKPw)] 中的 I/O 子程序库 io32.inc/.lib
