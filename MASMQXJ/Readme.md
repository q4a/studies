[郑州大学 汇编语言程序设计](https://www.icourse163.org/course/ZZU-1001796025) 示例练习代码  
授课老师 郑州大学 钱晓捷 张青

示例工程使用 [NMake](https://docs.microsoft.com/en-us/cpp/build/nmake-reference) 管理构建

    nmake /nologo                       # 默认以 Debug 配置构建
    nmake /nologo config=Release        # 以 Release 配置构建
    nmake /nologo clean                 # 清理 Debug 构建时生成的中间文件和结果文件
    nmake /nologo clean config=Release  # 清理 Release 构建时生成的中间文件和结果文件
    windbg -WF <Project>.wew            # 用 WinDbg 打开调试工作区文件

# 示例工程说明

**C8_3_Module**  
C/C++-Assembly 混合编程工程  
需要 VC 6.0 工具链，含 MASM 汇编器、MSVC 编译器，及 MSVCRT 和 WinAPI 库 (.h/.lib)

Microsoft Visual Studio 6.0.zip [[百度网盘 提取码 zwld](https://pan.baidu.com/s/1z_Ds4yGsOlzJ8OIuLaQDVA)]  
该 VC 6.0 开发包由以下开发包整合而成：
1. VS 6.0 Enterprise 中的 VC 6.0 部分
2. VS 6.0 SP 6
3. VC 6.0 Processor Pack 含 MASM 6.15.8803 汇编器

**除 C8_3_Module 之外的其它示例**  
依赖本课程教学的 I/O 子程序库 io32.inc/.lib

MASM 6 QXJ 开发包 [[百度网盘 提取码 pxck](https://pan.baidu.com/s/1tQoRc_Q_qd1p2w2NfldKPw)]  
该 MASM 6 开发包由以下开发包整合而成：
1. 本课程配套的 MASM 6 开发包
2. VS 6.0 Enterprise + SP6 中的 NMake 构建工具
3. VC 6.0 Processor Pack 中的 MASM 6.15.8803 汇编器
