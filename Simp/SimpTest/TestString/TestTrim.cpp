// TestTrim.cpp
//

#include "StdAfx.h"
#include "SimpTest.h"
#include "TestString.h"

////////////////////////////////////////////////////////////////////////////////
// 测试用例
////////////////////////////////////////////////////////////////////////////////

void TestTrimLeft_01(BOOL turnOn);
void TestTrimLeft_02(BOOL turnOn);
void TestTrimRight_01(BOOL turnOn);
void TestTrimRight_02(BOOL turnOn);
void TestTrim_01(BOOL turnOn);
void TestTrim_02(BOOL turnOn);

void TestIsSpace(BOOL turnOn);
void TestCRTStrCpy(BOOL turnOn);

////////////////////////////////////////////////////////////////////////////////
// 测试函数
////////////////////////////////////////////////////////////////////////////////

void TestTrim(BOOL turnOn) {
    SIMP_OFF_DO(turnOn, return);

    TestCRTStrCpy(FALSE);
    TestIsSpace(FALSE);
    TestTrimLeft_01(FALSE);
    TestTrimLeft_02(FALSE);
    TestTrimRight_01(FALSE);
    TestTrimRight_02(FALSE);
    TestTrim_01(FALSE);
    TestTrim_02(TRUE);
}

void TestCRTStrCpy(BOOL turnOn) {
    SIMP_OFF_DO(turnOn, return);
    PRINT_FUNC_BEGIN;

    _TCHAR dst[8];
    const _TCHAR* srcs[] = {
        // NULL,
        _T(""),
        _T("1234567"),
        _T("12345678"),
    };

    // 当源字符串和目标缓冲区重叠时，strcpy_s、strncpy_s 的行为是无定义的
    // The behavior of strcpy_s is undefined if the source and destination strings overlap.
    // The behavior of strncpy_s is undefined if the source and destination strings overlap.

#if 0
    // 当缓冲区太小时 _tcscpy_s 产生 Assert，不返回错误码，除非设置 Parameter Validation 为继续执行
    for (size_t i = 0; i < _countof(srcs); i++) {
        errno_t err = _tcscpy_s(dst, _countof(dst), srcs[i]);
        if (err != 0)
            _tperror(_T("_tcscpy_s"));

        _tprintf(_T("%d. Dest: [%s]\n"), i, dst);
    }
#endif

    // 当缓冲区太小时 _tcsncpy_s 使用 _TRUNCATE 截断超出缓冲区的字符串
    // 当不用 _TRUNCATE 时，_tcsncpy_s 和 _tcscpy_s 相似，产生 Assert
    for (size_t i = 0; i < _countof(srcs); i++) {
        errno_t err = _tcsncpy_s(dst, _countof(dst), srcs[i], _TRUNCATE);
        if (err != 0) {

            // VC2005 测试：_tcserror 还不能识别 STRUNCATE 错误码 (80)，得到对应的错误描述。只能得到 Unknown error
            // err = EINVAL;        // 22
            // err = STRUNCATE;     // 80

            // _tcserror 为线程不安全函数，产生 C4996 警告，使用 _CRT_SECURE_NO_WARNINGS 关闭警告
            // _ftprintf(stderr, _T("_tcscpy_s: %s (%d)\n"), _tcserror(err), err);

            _TCHAR msg[100];
            _tcserror_s(msg, _countof(msg), err);
            _ftprintf(stderr, _T("_tcscpy_s: %s (%d)\n"), msg, err);
        }

        _tprintf(_T("%d. Dest: [%s]\n"), i, dst);
    }

    PRINT_FUNC_END;
}

void TestIsSpace(BOOL turnOn) {
    SIMP_OFF_DO(turnOn, return);
    PRINT_FUNC_BEGIN;

    _tprintf(_T("Current Locale: %s\n"), _tsetlocale(LC_ALL, NULL));
    _TCHAR ws[] = _T(" \f\n\r\t\v　");

    // NOTE:
    // 设置简体中文 locale = chs 时，_istspace 会识别中文全角空格为空白字符 (Unicode=0x3000)
    // _istspace 不识别 \0 为空白字符

    size_t sz = _countof(ws);
    for (size_t i = 0; i < sz; i++)
        _tprintf(_T("%d. Character (%04X): %s\n"), i, ws[i], (_istspace(ws[i]) ? _T("white space") : _T("non white space")));

    PRINT_FUNC_END;
}

void TestTrimLeft_01(BOOL turnOn) {
    SIMP_OFF_DO(turnOn, return);
    PRINT_FUNC_BEGIN;

    _TCHAR dst[8];
    const _TCHAR* srcs[] = {
        NULL,
        _T(""),
        _T("  \t　"),
        _T("  \t　123   "),
        _T("  \t　1234567"),
        _T("  \t　12345678")
    };

    for (size_t i = 0; i < _countof(srcs); i++) {
        errno_t err = Simp::TrimLeftAlert(srcs[i], dst, _countof(dst));

        if (err == 0)
            _tprintf(_T("%d. Trimed: [%s]\n"), i, dst);
        else if (err == STRUNCATE)
            _tprintf(_T("%d. Trimed: [%s] Truncated\n"), i, dst);
        else
            _tprintf(_T("%d. Trim failed\n"), i);
    }

    PRINT_FUNC_END;
}

void TestTrimLeft_02(BOOL turnOn) {
    SIMP_OFF_DO(turnOn, return);
    PRINT_FUNC_BEGIN;

    _TCHAR* srcs[] = {
        NULL,
        _tcsdup(_T("")),
        _tcsdup(_T("  \t　")),
        _tcsdup(_T("  \t　123   ")),
        _tcsdup(_T("  \t　1234567")),
        _tcsdup(_T("  \t　12345678"))
    };

    for (size_t i = 0; i < _countof(srcs); i++) {
        errno_t err = Simp::TrimLeftAlert(srcs[i]);

        if (err == 0)
            _tprintf(_T("%d. Trimed: [%s]\n"), i, srcs[i]);
        else if (err == STRUNCATE)
            _tprintf(_T("%d. Trimed: [%s] Truncated\n"), i, srcs[i]);
        else
            _tprintf(_T("%d. Trim failed\n"), i);
    }

    for (size_t i = 0; i < _countof(srcs); i++)
        free(srcs[i]);

    PRINT_FUNC_END;
}

void TestTrimRight_01(BOOL turnOn) {
    SIMP_OFF_DO(turnOn, return);
    PRINT_FUNC_BEGIN;

    _TCHAR dst[8];
    const _TCHAR* srcs[] = {
        NULL,
        _T(""),
        _T("  \t　"),
        _T("   123  \t　"),
        _T("1234567  \t　"),
        _T("12345678  \t　")
    };

    for (size_t i = 0; i < _countof(srcs); i++) {
        errno_t err = Simp::TrimRightAlert(srcs[i], dst, _countof(dst));

        if (err == 0)
            _tprintf(_T("%d. Trimed: [%s]\n"), i, dst);
        else if (err == STRUNCATE)
            _tprintf(_T("%d. Trimed: [%s] Truncated\n"), i, dst);
        else
            _tprintf(_T("%d. Trim failed\n"), i);
    }

    PRINT_FUNC_END;
}

void TestTrimRight_02(BOOL turnOn) {
    SIMP_OFF_DO(turnOn, return);
    PRINT_FUNC_BEGIN;

    _TCHAR* srcs[] = {
        NULL,
        _tcsdup(_T("")),
        _tcsdup(_T("  \t　")),
        _tcsdup(_T("   123  \t　")),
        _tcsdup(_T("1234567  \t　")),
        _tcsdup(_T("12345678  \t　"))
    };

    for (size_t i = 0; i < _countof(srcs); i++) {
        errno_t err = Simp::TrimRightAlert(srcs[i]);

        if (err == 0)
            _tprintf(_T("%d. Trimed: [%s]\n"), i, srcs[i]);
        else if (err == STRUNCATE)
            _tprintf(_T("%d. Trimed: [%s] Truncated\n"), i, srcs[i]);
        else
            _tprintf(_T("%d. Trim failed\n"), i);
    }

    for (size_t i = 0; i < _countof(srcs); i++)
        free(srcs[i]);

    PRINT_FUNC_END;
}

void TestTrim_01(BOOL turnOn) {
    SIMP_OFF_DO(turnOn, return);
    PRINT_FUNC_BEGIN;

    _TCHAR dst[8];
    const _TCHAR* srcs[] = {
        NULL,
        _T(""),
        _T("  \t　"),
        _T("  \t　123   "),
        _T("  \t　1234567"),
        _T("  \t　12345678"),
        _T("   123  \t　"),
        _T("1234567  \t　"),
        _T("12345678  \t　"),
        _T("  \t　12   67  \t　"),
        _T("  \t　1234567  \t　"),
        _T("  \t　12345678  \t　")
    };

    for (size_t i = 0; i < _countof(srcs); i++) {
        errno_t err = Simp::TrimAlert(srcs[i], dst, _countof(dst));

        if (err == 0)
            _tprintf(_T("%d. Trimed: [%s]\n"), i, dst);
        else if (err == STRUNCATE)
            _tprintf(_T("%d. Trimed: [%s] Truncated\n"), i, dst);
        else
            _tprintf(_T("%d. Trim failed\n"), i);
    }

    PRINT_FUNC_END;
}

void TestTrim_02(BOOL turnOn) {
    SIMP_OFF_DO(turnOn, return);
    PRINT_FUNC_BEGIN;

    _TCHAR* srcs[] = {
        NULL,
        _tcsdup(_T("")),
        _tcsdup(_T("  \t　")),
        _tcsdup(_T("  \t　123   ")),
        _tcsdup(_T("  \t　1234567")),
        _tcsdup(_T("  \t　12345678")),
        _tcsdup(_T("   123  \t　")),
        _tcsdup(_T("1234567  \t　")),
        _tcsdup(_T("12345678  \t　")),
        _tcsdup(_T("  \t　12   67  \t　")),
        _tcsdup(_T("  \t　1234567  \t　")),
        _tcsdup(_T("  \t　12345678  \t　"))
    };

    for (size_t i = 0; i < _countof(srcs); i++) {
        errno_t err = Simp::TrimAlert(srcs[i]);

        if (err == 0)
            _tprintf(_T("%d. Trimed: [%s]\n"), i, srcs[i]);
        else if (err == STRUNCATE)
            _tprintf(_T("%d. Trimed: [%s] Truncated\n"), i, srcs[i]);
        else
            _tprintf(_T("%d. Trim failed\n"), i);
    }

    for (size_t i = 0; i < _countof(srcs); i++)
        free(srcs[i]);

    PRINT_FUNC_END;
}
