// BuoyInfo.cpp
//

#include "StdAfx.h"
#include "BuoyInfo.h"

#include "BuoyMsg.h"

////////////////////////////////////////////////////////////////////////////////
// 全局量
////////////////////////////////////////////////////////////////////////////////

// 原来的工作目录
_TCHAR* OldWorkDir;

////////////////////////////////////////////////////////////////////////////////
// 初始化和清理
////////////////////////////////////////////////////////////////////////////////

void Init();
void Uninit();

////////////////////////////////////////////////////////////////////////////////
// 程序入口
////////////////////////////////////////////////////////////////////////////////

int _tmain(int argc, _TCHAR* argv[])
{
    Init();

    TestMsgDescTbl(FALSE);
    TestMsgTbl(TRUE);

    Uninit();
    _putts(_T("Press any key to Exit."));
    _gettch();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
// 初始化和清理
////////////////////////////////////////////////////////////////////////////////

// 初始化运行环境
void Init()
{
#define _USE_CRT_LOCALE

#if _MSC_VER > 1400
#define _USE_IOS_LOCALE
#endif

// CRT 全局 locale 和 iostream imbue locale 冲突
// VC 2005 问题 (_MSC_VER = 1400)
// VC 2010 正常 (_MSC_VER = 1600)
#if _MSC_VER <= 1400 && defined(_USE_CRT_LOCALE) && defined(_USE_IOS_LOCALE)
#error cannot use CRT global locale and iostream imbue locale at the same time, when _MSC_VER <= 1400
#endif

#ifdef _USE_CRT_LOCALE
    _tsetlocale(LC_ALL, _T(""));
#endif

#ifdef _USE_IOS_LOCALE
    // 设置 C++ iostream 标准 IO 流 locale
    std::locale loc(std::locale(""), std::locale::classic(), std::locale::numeric);
    tcout.imbue(loc);
    tcerr.imbue(loc);
    tcin.imbue(loc);
#endif

    // 设置 CRT 调试输出
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);

    // 设置当前 exe 文件的目录为工作目录
    _TCHAR modDir[BUF_SIZE];
    OldWorkDir = _tgetcwd(NULL, 0);
    Simp::GetModuleDir(GetModuleHandle(NULL), modDir, BUF_SIZE);
    _tchdir(modDir);
}

// 清理运行环境
void Uninit()
{
    // 恢复原来的工作目录
    _tchdir(OldWorkDir);
    free(OldWorkDir);

    // 因为静态对象在 Uninit 之后析构, 所以在下句之前需要手工释放含动态存储的静态对象, 否则会有误判
    _CrtDumpMemoryLeaks();
}
