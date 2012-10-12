// TestString.cpp
//

#include "StdAfx.h"
#include "SimpTest.h"
#include "TestString.h"

////////////////////////////////////////////////////////////////////////////////
// 名字空间
////////////////////////////////////////////////////////////////////////////////

using Simp::tstring;
using Simp::tcin;
using Simp::tcout;
using Simp::tcerr;
using Simp::ToTchar;

////////////////////////////////////////////////////////////////////////////////
// 全局变量
////////////////////////////////////////////////////////////////////////////////

// 保存全局 locale 名称
static _TCHAR OldLocale[BUF_SIZE];

////////////////////////////////////////////////////////////////////////////////
// 测试辅助
////////////////////////////////////////////////////////////////////////////////

// 调试输出当前的 locale
// 当 callFunc = 0 时, 输出 module!report_current_locale: 前缀
// 当 callFunc != 0 时, 输出 module!callFunc: 前缀
void ReportCurrentLocale(const _TCHAR* callFunc, BOOL turnOn);

// 设置全局 locale, 将旧 locale 名保存到 oldLoc
void SetGlobalLocale(const _TCHAR* loc, __out _TCHAR* oldLoc, size_t bufSize, const _TCHAR* callFunc, BOOL reportOn);

// 设置全局 locale, 将旧 locale 名保存到全局变量 OldLocale
#define SET_GLOBAL_LOCALE(loc, reportOn) \
    SetGlobalLocale(loc, OldLocale, _countof(OldLocale), _T(__FUNCTION__), reportOn)

// 恢复 locale
void RestoreGlobalLocale(_TCHAR* loc, const _TCHAR* callFunc, BOOL reportOn);

// 恢复 locale 为全局变量 OldLocale
#define RESTORE_GLOBAL_LOCALE(reportOn) \
    RestoreGlobalLocale(OldLocale, _T(__FUNCTION__), reportOn)

////////////////////////////////////////////////////////////////////////////////
// 测试用例
////////////////////////////////////////////////////////////////////////////////

void TestMbsToWcs(BOOL turnOn);

////////////////////////////////////////////////////////////////////////////////
// 测试函数
////////////////////////////////////////////////////////////////////////////////

void TestString(BOOL turnOn)
{
    SIMP_OFF_DO(turnOn, return);

    TestMbsToWcs(TRUE);
}

////////////////////////////////////////////////////////////////////////////////
// 测试辅助
////////////////////////////////////////////////////////////////////////////////

void ReportCurrentLocale(const _TCHAR* callFunc, BOOL turnOn)
{
    SIMP_OFF_DO(turnOn, return);

    const _TCHAR* loc = _tsetlocale(LC_ALL, 0);
    _ASSERTE(loc != 0);

    if (callFunc == NULL)
        MY_RPT(_CRT_WARN, "current locale: %s", loc);
    else
        MY_RPT(_CRT_WARN, "%s: current locale: %s", callFunc, loc);
}

void SetGlobalLocale(const _TCHAR* loc, __out _TCHAR* oldLoc, size_t bufSize, const _TCHAR* callFunc, BOOL reportOn)
{
    ReportCurrentLocale(callFunc, reportOn);
    _tcscpy_s(oldLoc, bufSize, _tsetlocale(LC_ALL, NULL));
    _tsetlocale(LC_ALL, loc);
    ReportCurrentLocale(callFunc, reportOn);
}

void RestoreGlobalLocale(_TCHAR* loc, const _TCHAR* callFunc, BOOL reportOn)
{
    _tsetlocale(LC_ALL, loc);
    ReportCurrentLocale(callFunc, reportOn);
}

////////////////////////////////////////////////////////////////////////////////
// 测试用例
////////////////////////////////////////////////////////////////////////////////

// 测试 sim_mbstowcs(), sim_alloc_mbstowcs()
void TestMbsToWcs(BOOL turnOn)
{
    SIMP_OFF_DO(turnOn, return);

    char mbstr[] = "abc汉字符123";
    const size_t WCSTR_BUF_SIZE = 5;
    wchar_t wcstrBuf[WCSTR_BUF_SIZE] = {0};
    wchar_t* wcstr = NULL;
    errno_t err = 0;

    SET_GLOBAL_LOCALE(_T(""), FALSE);   // 设置全局 locale

    // sim_mbstowcs() 的参数 loc = 0 时, 在全局 locale (setlocale()) 下进行转换
    MY_CALL_RPT(_CRT_WARN, err, Simp::MbsToWcs, (mbstr, wcstrBuf, _countof(wcstrBuf)));
    MY_CALL_RPT(_CRT_WARN, err, Simp::MbsToWcsNew, (mbstr, wcstr));

    free(wcstr);

    RESTORE_GLOBAL_LOCALE(FALSE);       // 恢复 locale
}
