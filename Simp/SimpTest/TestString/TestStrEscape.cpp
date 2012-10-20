// TestStrEscape.cpp
//

#include "StdAfx.h"
#include "SimpTest.h"

#include "TestString.h"

////////////////////////////////////////////////////////////////////////////////
// √˚◊÷ø’º‰
////////////////////////////////////////////////////////////////////////////////

using Simp::tcin;
using Simp::tcout;

////////////////////////////////////////////////////////////////////////////////
// ≤‚ ‘”√¿˝
////////////////////////////////////////////////////////////////////////////////

void TestMyString(BOOL turnOn);
void TestStrEscape_01(BOOL turnOn);
void TestStrEscape_02(BOOL turnOn);

////////////////////////////////////////////////////////////////////////////////
// ≤‚ ‘∫Ø ˝
////////////////////////////////////////////////////////////////////////////////

void TestStrEscape(BOOL turnOn) {
    SIMP_OFF_DO(turnOn, return);

    TestMyString(FALSE);
    TestStrEscape_01(FALSE);
    TestStrEscape_02(TRUE);
}

////////////////////////////////////////////////////////////////////////////////
// ≤‚ ‘”√¿˝
////////////////////////////////////////////////////////////////////////////////

void TestMyString(BOOL turnOn) {
    SIMP_OFF_DO(turnOn, return);
    PRINT_FUNC_BEGIN;

    typedef Simp::StringT<_TCHAR> String;

    String str;
    tcout << _T("Input string: ");
    tcin >> str;
    tcout << _T("String: ") << str << _T("\nSize: ") << str.size() << _T("\n");

    PRINT_FUNC_END;
}

// ≤‚ ‘: ◊÷∑˚¥Æ◊™“Â∫Ø ˝ StrEscape
void TestStrEscape_01(BOOL turnOn) {
    SIMP_OFF_DO(turnOn, return);
    PRINT_FUNC_BEGIN;

    _TCHAR src[BUF_SIZE];
    _tprintf(_T("Input string: "));
    _getts_s(src, BUF_SIZE);

    _tprintf(_T("Origin: [%s]\n"), src);
    size_t size = _tcslen(src) + 1;
    _TCHAR* dst = new _TCHAR[size];

    errno_t err = Simp::StrEscape(src, dst, size);
    if (err != 0)
        _tprintf(_T("StrEscape error %d: %s\n"), err, SIMP_CRTSTRERR(BUF_SIZE, err));
    else
        _tprintf(_T("Escaped: [%s]\n"), dst);

    delete[] dst;

    PRINT_FUNC_END;
}

// ≤‚ ‘: ◊÷∑˚¥Æ◊™“Â∫Ø ˝ StrEscape (InPlace)
void TestStrEscape_02(BOOL turnOn) {
    SIMP_OFF_DO(turnOn, return);
    PRINT_FUNC_BEGIN;

    _TCHAR src[BUF_SIZE];
    _tprintf(_T("Input string: "));
    _getts_s(src, BUF_SIZE);

    _tprintf(_T("Origin: [%s]\n"), src);
    size_t size = _tcslen(src) + 1;

    errno_t err = Simp::StrEscape(src);
    if (err != 0)
        _tprintf(_T("StrEscape error %d: %s\n"), err, SIMP_CRTSTRERR(BUF_SIZE, err));
    else
        _tprintf(_T("Escaped: [%s]\n"), src);

    PRINT_FUNC_END;
}
