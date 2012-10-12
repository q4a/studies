// TestFile.cpp
//

#include "StdAfx.h"
#include "SimpTest.h"
#include "TestFile.h"

////////////////////////////////////////////////////////////////////////////////
// 名字空间
////////////////////////////////////////////////////////////////////////////////

using Simp::tstring;
using Simp::tcin;
using Simp::tcout;
using Simp::tcerr;
using Simp::ToTchar;

using Simp::StdioFile;

////////////////////////////////////////////////////////////////////////////////
// 全局变量
////////////////////////////////////////////////////////////////////////////////

enum ACCESS_MODE {
    AC_EXIST    = 0,
    AC_WRITE    = 2,
    AC_READ     = 4
};

const _TCHAR* FILE_ENCODING[] = {_T("ANSI"), _T("UTF-8"), _T("UTF-16LE"), _T("UNICODE")};

////////////////////////////////////////////////////////////////////////////////
// 测试用例
////////////////////////////////////////////////////////////////////////////////

void TestReadText(BOOL turnOn);

////////////////////////////////////////////////////////////////////////////////
// 测试函数
////////////////////////////////////////////////////////////////////////////////

void TestStdio(BOOL turnOn)
{
    SIMP_OFF_DO(turnOn, return);
    TestReadText(TRUE);
}

////////////////////////////////////////////////////////////////////////////////
// 测试用例
////////////////////////////////////////////////////////////////////////////////

// ANSI, UTF-8, UTF-16 (UCS-2) 编码文件读取
void TestReadText(BOOL turnOn)
{
    SIMP_OFF_DO(turnOn, return);
    PRINT_FUNC_BEGIN;

    int i;
    int e;
    _TCHAR fname[BUF_SIZE];
    _TCHAR mode[BUF_SIZE];

    // 取得文件名
    while (TRUE) {
        _tprintf(_T("file name: "));
        _getts_s(fname, _countof(fname));
        if (_taccess_s(fname, AC_READ) == 0)
            break;
        _tperror(fname);
    }

    // 取得文件编码
    while (TRUE) {
        _tprintf(_T("ecoding:"));
        for (i = 0; i < _countof(FILE_ENCODING); i++)
            _tprintf(_T(" %d. %s"), i + 1, FILE_ENCODING[i]);
        _tprintf(_T(": "));
        _getts_s(mode, _countof(mode));
#pragma warning(push)
#pragma warning(disable: 4996)
        if (_stscanf(mode, _T("%d"), &e) == 1 && e >= 1 && e <= _countof(FILE_ENCODING))
#pragma warning(pop)
            break;
    }
    e--;

    // TEST:
    _tprintf(_T("file name: %s\n"), fname);
    _tprintf(_T("encoding: %s\n"), FILE_ENCODING[e]);

    _stprintf_s(mode, _countof(mode), _T("r, ccs=%s"), FILE_ENCODING[e]);
    StdioFile file;
    file.Open(fname, mode);

    // 读取文件行
    _TCHAR* line;
    _TCHAR  buf[BUF_SIZE];
    for (i = 0; TRUE; i++) {
        line = file.Gets(buf, _countof(buf));   // gets 保留行尾的 \n
        if (line == NULL)
            break;
        _tprintf(_T("%04d|%s"), i + 1, line);
    }

    if (file.Eof())
        _tprintf(_T("\nread file end\n"));
    else if (file.Error()) {
#pragma warning(push)
#pragma warning(disable: 4996)
        _ftprintf(stderr, _T("\nread file error: %s (%d)\n"), _tcserror(errno), errno);
#pragma warning(pop)
    }

    PRINT_FUNC_END;
}
