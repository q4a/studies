// TestLog.cpp
//

#include "StdAfx.h"
#include "SimpTest.h"
#include "TestLog.h"

////////////////////////////////////////////////////////////////////////////////
// √˚◊÷ø’º‰
////////////////////////////////////////////////////////////////////////////////

using Simp::LogBaseT;
using Simp::LogDebugOutT;
namespace LOG_LVL = Simp::LOG_LVL;

using Simp::tcin;
using Simp::tcout;
using Simp::tcerr;
using Simp::ToTchar;

////////////////////////////////////////////////////////////////////////////////
// ≤‚ ‘”√¿˝
////////////////////////////////////////////////////////////////////////////////

void TestDbgoutLog(BOOL turnOn);

////////////////////////////////////////////////////////////////////////////////
// ≤‚ ‘∫Ø ˝
////////////////////////////////////////////////////////////////////////////////

void TestLog(BOOL turnOn)
{
    SIMP_OFF_DO(turnOn, return);
    TestDbgoutLog(TRUE);
}

////////////////////////////////////////////////////////////////////////////////
// ≤‚ ‘”√¿˝
////////////////////////////////////////////////////////////////////////////////

// ≤‚ ‘ LogDebugOut
void TestDbgoutLog(BOOL turnOn)
{
    SIMP_OFF_DO(turnOn, return);
    PRINT_FUNC_BEGIN;

    int iv = 42;
    double dv = 3.14159;
    const _TCHAR* str = _T("hello world!");

    std::auto_ptr<LogDebugOutT<_TCHAR> > log(new LogDebugOutT<_TCHAR>(BUF_SIZE, LOG_LVL::LEVEL_WARNING));

    log->Log(FMT("This is a log test: %d, %f, %s\n"), iv, dv, str);

    log->Log(LOG_LVL::LEVEL_DEBUG, FMT("This is a log test: %d, %f, %s\n"), ++iv, dv, str);
    log->Log(LOG_LVL::LEVEL_INFO, FMT("This is a log test: %d, %f, %s\n"), ++iv, dv, str);
    log->Log(LOG_LVL::LEVEL_WARNING, FMT("This is a log test: %d, %f, %s\n"), ++iv, dv, str);
    log->Log(LOG_LVL::LEVEL_ERROR, FMT("This is a log test: %d, %f, %s\n"), ++iv, dv, str);
    log->Log(LOG_LVL::LEVEL_CRITICAL, FMT("This is a log test: %d, %f, %s\n"), ++iv, dv, str);

    log->Log(FMT("This is a log test: %d, %f, %s\n"), ++iv, dv, str);

    PRINT_FUNC_END;
}
