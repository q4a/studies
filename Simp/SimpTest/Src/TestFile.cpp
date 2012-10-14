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

using Simp::StdioFile;

////////////////////////////////////////////////////////////////////////////////
// 全局量
////////////////////////////////////////////////////////////////////////////////

enum ACCESS_MODE {
    AC_EXIST    = 0,
    AC_WRITE    = 2,
    AC_READ     = 4
};

const int FILE_ENCODING_NOSPEC = 0;
const _TCHAR* FILE_ENCODING[] = {_T("[NOSPEC]"), _T("ANSI"), _T("UTF-8"), _T("UTF-16LE"), _T("UNICODE")};

////////////////////////////////////////////////////////////////////////////////
// 测试用例
////////////////////////////////////////////////////////////////////////////////

void ReadText_01(BOOL turnOn);
void ReadLineText_01(BOOL turnOn);

////////////////////////////////////////////////////////////////////////////////
// 测试函数
////////////////////////////////////////////////////////////////////////////////

void TestReadLine(BOOL turnOn) {
    SIMP_OFF_DO(turnOn, return);
    ReadLineText_01(TRUE);
}

void TestStdio(BOOL turnOn) {
    SIMP_OFF_DO(turnOn, return);
    ReadText_01(TRUE);
}

////////////////////////////////////////////////////////////////////////////////
// 测试用例
////////////////////////////////////////////////////////////////////////////////

// 测试 Simp::ReadLine
void ReadLineText_01(BOOL turnOn) {
    SIMP_OFF_DO(turnOn, return);
    PRINT_FUNC_BEGIN;

    _TCHAR fname[BUF_SIZE];

    // 取得文件名
    while (TRUE) {
        _tprintf(_T("File name: "));
        _getts_s(fname, _countof(fname));
        if (_taccess_s(fname, AC_READ) == 0)
            break;
        _tperror(fname);
    }

    // TEST:
    _tprintf(_T("File name: %s\n"), fname);

    StdioFile file;
    file.Open(fname, _T("r"));

    // 使用 Simp::ReadLine 读取文件行
    Simp::ReadLine<_TCHAR> readLine;
    readLine.SetBufSize(8);

    int i = 0;
    // Simp::ReadLine 基于 CRT gets, 所以含行尾 \n
    while (readLine.Read(file.Stream()) == 0)
        _tprintf(_T("%04d|%s"), i++, readLine.Line());

    if (file.Eof())
        _putts(_T("\n----- Read File End -----"));
    else if (file.Error()) {
#pragma warning(push)
#pragma warning(disable: 4996)
        _ftprintf(stderr, _T("\nRead file error: %s (%d)\n"), _tcserror(errno), errno);
#pragma warning(pop)
    }

    PRINT_FUNC_END;
}

// ANSI, UTF-8, UTF-16 (UCS-2) 编码文件读取
void ReadText_01(BOOL turnOn) {
    SIMP_OFF_DO(turnOn, return);
    PRINT_FUNC_BEGIN;

    int i;
    int e;
    _TCHAR fname[BUF_SIZE];
    _TCHAR mode[BUF_SIZE];

    // 取得文件名
    while (TRUE) {
        _tprintf(_T("File name: "));
        _getts_s(fname, _countof(fname));
        if (_taccess_s(fname, AC_READ) == 0)
            break;
        _tperror(fname);
    }

    // 取得文件编码
    while (TRUE) {
        _tprintf(_T("Ecoding:"));
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
    _tprintf(_T("File name: %s\n"), fname);
    _tprintf(_T("Encoding: %s\n"), FILE_ENCODING[e]);

    // VC 2005 测试结果:
    // ccs=ANSI 参数错误, 产生 Assert. 要读写 ANSI 编码文件, 请不要指定任何 css= 编码
    // ccs=UTF-8 可用来读写 UTF-8 (NO BOM) 编码文件
    // ccs=UTF-16LE 可用来读写 UTF-16LE (NO BOM) 和 Unicode (NO BOM) 编码文件
    // ccs=UNICODE 读写 Unicode (NO BOM) 编码文件时乱码

    if (e == FILE_ENCODING_NOSPEC)
        _stprintf_s(mode, _countof(mode), _T("r"));
    else
        _stprintf_s(mode, _countof(mode), _T("r, ccs=%s"), FILE_ENCODING[e]);
    StdioFile file;
    file.Open(fname, mode);

    // 读取文件行
    _TCHAR* line;
    _TCHAR  buf[BUF_SIZE];
    for (i = 0; TRUE; i++) {
        line = file.Gets(buf, _countof(buf));   // gets 含行尾 \n
        if (line == NULL)
            break;
        _tprintf(_T("%04d|%s"), i + 1, line);
    }

    if (file.Eof())
        _putts(_T("\n----- Read File End -----"));
    else if (file.Error()) {
#pragma warning(push)
#pragma warning(disable: 4996)
        _ftprintf(stderr, _T("\nRead file error: %s (%d)\n"), _tcserror(errno), errno);
#pragma warning(pop)
    }

    PRINT_FUNC_END;
}
