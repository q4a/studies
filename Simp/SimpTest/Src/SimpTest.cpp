// SimpTest.cpp
//

#include "StdAfx.h"
#include "SimpTest.h"
#include "TestString.h"
#include "TestMemory.h"
#include "TestDebug.h"
#include "TestThread.h"
#include "TestLog.h"
#include "TestFile.h"

////////////////////////////////////////////////////////////////////////////////
// 名字空间
////////////////////////////////////////////////////////////////////////////////

using Simp::LogBaseT;
namespace LOG_LVL = Simp::LOG_LVL;

using Simp::tcin;
using Simp::tcout;
using Simp::tcerr;

////////////////////////////////////////////////////////////////////////////////
// 全局变量
////////////////////////////////////////////////////////////////////////////////

// 原来的工作目录
static _TCHAR* OldWorkDir;

// 日志对象
LogBaseT<char>*     LogA;
LogBaseT<wchar_t>*  LogW;
LogBaseT<_TCHAR>*   Log;

////////////////////////////////////////////////////////////////////////////////
// 初始化和清理函数
////////////////////////////////////////////////////////////////////////////////

void Init();
void Uninit();

////////////////////////////////////////////////////////////////////////////////
// 程序入口函数
////////////////////////////////////////////////////////////////////////////////

int _tmain(int argc, _TCHAR* argv[]) {
    Init();

    try {
        TestString(FALSE);
        TestMemory(TRUE);
        TestDbgout(FALSE);
        TestThread(FALSE);
        TestLog(FALSE);
        TestStdio(FALSE);
    }
    catch (std::exception& e) {
        LogA->Log(LOG_LVL::LEVEL_ERROR, FMTA("std::exception: what: %s, type: %s"), e.what(), typeid(e).name());
    }
    catch (...) {
        Log->Log(LOG_LVL::LEVEL_ERROR, FMT("unknown exception"));
    }

    Uninit();
    _putts(_T("Press any key to Exit."));
    _gettch();
    return 0;
}

// 初始化运行环境
void Init() {
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

    // 设置日志对象
    LogA = Simp::DebugOutLogT<char>(LOG_LVL::LEVEL_DEBUG, BUF_SIZE);
    LogW = Simp::DebugOutLogT<wchar_t>(LOG_LVL::LEVEL_DEBUG, BUF_SIZE);
#ifdef _UNICODE
    Log = LogW;
#else
    Log = LogA;
#endif
}

// 清理运行环境
void Uninit() {
    // 恢复原来的工作目录
    _tchdir(OldWorkDir);
    free(OldWorkDir);

    // 手工释放日志对象
    LogA->Destroy();
    LogW->Destroy();

    // 静态对象在 Uninit 之后析构, 需要手工释放含动态存储的静态对象, 否则会有误判
    _CrtDumpMemoryLeaks();
}
