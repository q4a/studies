// TestStrCpy.cpp
//

#include "StdAfx.h"
#include "SimpTest.h"
#include "Common.h"

#include "TestString.h"

////////////////////////////////////////////////////////////////////////////////
// 测试用例
////////////////////////////////////////////////////////////////////////////////

void TestStrCpy(BOOL turnOn);
void TestStrCpy_01(BOOL turnOn);
void TestStrCpy_02(BOOL turnOn);
void TestStrCpy_03(BOOL turnOn);
void TestStrCpy_04(BOOL turnOn);

////////////////////////////////////////////////////////////////////////////////
// 测试函数
////////////////////////////////////////////////////////////////////////////////

void MyInvalidParameterHandler(const wchar_t* expression, const wchar_t* function, const wchar_t* file, unsigned int line, uintptr_t pReserved) {
    _RPTW3(_CRT_ERROR, L"Invalid parameter detected in function %s. File: %s Line: %d\n", function, file, line);
    _RPTW1(_CRT_ERROR, L"Expression: %s\n", expression);
}

void TestStrCpy(BOOL turnOn) {
    SIMP_OFF_DO(turnOn, return);

    srand((unsigned) time(NULL));
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);
    _set_invalid_parameter_handler(MyInvalidParameterHandler);

    TestStrCpy_01(FALSE);
    TestStrCpy_02(FALSE);
    TestStrCpy_03(FALSE);
    TestStrCpy_04(TRUE);

    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_WNDW);
}

// 测试 _tcscpy_s 的目标缓冲区过小检测
// 设置 InvalidParameterHandler 让 _tcscpy_s 返回控制，代替默认行为 Assert + 终止程序
void TestStrCpy_01(BOOL turnOn) {
    SIMP_OFF_DO(turnOn, return);

    PRINT_FUNC_BEGIN;

    const size_t BUF_SIZE1 = 8;
    _TCHAR strDest[BUF_SIZE1];
    errno_t err = _tcscpy_s(strDest, _countof(strDest), _T("12345678"));

#pragma warning(push)
#pragma warning(disable: 4996)
    _tprintf(_T("Error: %s (%d)\n"), _tcserror(err), err);
#pragma warning(pop)

    PRINT_FUNC_END;
}

template <BOOL UseCRTStrCpy>
void TestStrCpySpeed(BOOL dumpStr, int round, size_t destBufSize, size_t srcBufSize) {
    _ASSERTE(round > 0);
    _ASSERTE(destBufSize > 0 && srcBufSize > 0);

    int i;
    UINT64 beginClock, endClock;
    UINT64* clocks = new UINT64[round];

    _TCHAR* strDest = new _TCHAR[destBufSize];
    _TCHAR* strSrc = new _TCHAR[srcBufSize];

    RandString(strSrc, srcBufSize, _T('0'), _T('z'));
    if (dumpStr)
        DumpString(_T("Source String"), strSrc);

    for (i = 0; i < round; i++) {
        ZeroMemory(strDest, destBufSize * sizeof(_TCHAR));
        beginClock = CRTClock();
        if (UseCRTStrCpy)
            _tcsncpy_s(strDest, destBufSize, strSrc, _TRUNCATE);
        else
            Simp::StrNCpy(strDest, destBufSize, strSrc, _TRUNCATE);
        endClock = CRTClock();
        clocks[i] = endClock - beginClock;
    }

    if (dumpStr)
        DumpString(_T("Dest String"), strDest);

    _tprintf(_T("Clocks: "));
    UINT64 sumClock = 0, avrgClock;
    for (i = 0; i < round - 1; i++) {
        _tprintf(_T("%I64d, "), clocks[i]);
        sumClock += clocks[i];
    }
    _tprintf(_T("%I64d\n"), clocks[i]);
    sumClock += clocks[i];
    avrgClock = sumClock / round;
    _tprintf(_T("Average Clocks: %I64d in %d Rounds\n"), avrgClock, round);

    delete[] strDest;
    delete[] strSrc;
    delete[] clocks;
}

inline
void TestMyStrCpySpeed(BOOL dumpStr, int round, size_t destBufSize, size_t srcBufSize) {
    TestStrCpySpeed<FALSE>(dumpStr, round, destBufSize, srcBufSize);
}

inline
void TestCRTStrCpySpeed(BOOL dumpStr, int round, size_t destBufSize, size_t srcBufSize) {
    TestStrCpySpeed<TRUE>(dumpStr, round, destBufSize, srcBufSize);
}

// 测试 StrNCpy 的正确性
void TestStrCpy_02(BOOL turnOn) {
    SIMP_OFF_DO(turnOn, return);

    PRINT_FUNC_BEGIN;

    const size_t DEST_BUF_SIZE = 90;
    const size_t SRC_BUF_SIZE = 64;

    _putts(_T("Test StrNCpy:"));
    TestMyStrCpySpeed(TRUE, 1, SRC_BUF_SIZE, DEST_BUF_SIZE);
    _putts(_T(""));

    PRINT_FUNC_END;
}

// 测试 CRT strcpy 和 StrNCpy 的效率
void TestStrCpy_03(BOOL turnOn) {
    SIMP_OFF_DO(turnOn, return);

    PRINT_FUNC_BEGIN;

    const size_t DEST_BUF_SIZE = 10 * 1024 * 1024;
    const size_t SRC_BUF_SIZE = DEST_BUF_SIZE + 64;

    _putts(_T("Test _tcsncpy_s Speed:"));
    TestCRTStrCpySpeed(FALSE, 100, DEST_BUF_SIZE, SRC_BUF_SIZE);
    _putts(_T(""));
    _putts(_T("Test StrNCpy Speed:"));
    TestMyStrCpySpeed(FALSE, 100, DEST_BUF_SIZE, SRC_BUF_SIZE);

    PRINT_FUNC_END;
}

// 测试带截断错误返回的 StrNCpy
void TestStrCpy_04(BOOL turnOn) {
    SIMP_OFF_DO(turnOn, return);

    PRINT_FUNC_BEGIN;

    _TCHAR dest[8];
    errno_t err = Simp::StrNCpyAlert(dest, _countof(dest), _T("123456"), _TRUNCATE);
    _tprintf(_T("dest: %s, errno: %d\n"), dest, err);
    err = Simp::StrNCpyAlert(dest, _countof(dest), _T("1234567"), _TRUNCATE);
    _tprintf(_T("dest: %s, errno: %d\n"), dest, err);
    err = Simp::StrNCpyAlert(dest, _countof(dest), _T("12345678"), _TRUNCATE);
    _tprintf(_T("dest: %s, errno: %d\n"), dest, err);

    PRINT_FUNC_END;
}
