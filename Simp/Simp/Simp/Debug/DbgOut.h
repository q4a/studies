////////////////////////////////////////////////////////////////////////////////
// 文    件 : DbgOut.h
// 功能说明 :
//   调试输出功能
//
// 版    本 : 1.0
// 作    者 : Breaker Zhao <breaker.zy_AT_gmail>
// 日    期 : 2011-10
// 授权许可 : Microsoft Public License <http://www.microsoft.com/en-us/openness/licenses.aspx#MPL>
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <Simp/Depends.h>
#include <Simp/Defs.h>

SIMP_NS_BEGIN

#ifdef _DEBUG

////////////////////////////////////////////////////////////////////////////////
// 接受任意个数参数的 SIMP_RPT
//

// char 版
#define SIMP_RPTA(rptType, fmt, ...) \
    (void) ((1 != _CrtDbgReport(rptType, 0, 0, 0, fmt, __VA_ARGS__)) || \
    (_CrtDbgBreak(), 0))

#define SIMP_RPTFA(rptType, fmt, ...) \
    (void) ((1 != _CrtDbgReport(rptType, __FILE__, __LINE__, 0, fmt, __VA_ARGS__)) || \
    (_CrtDbgBreak(), 0))

// wchar_t 版
#define SIMP_RPTW(rptType, fmt, ...) \
    (void) ((1 != _CrtDbgReportW(rptType, 0, 0, 0, fmt, __VA_ARGS__)) || \
    (_CrtDbgBreak(), 0))

#define SIMP_RPTFW(rptType, fmt, ...) \
    (void) ((1 != _CrtDbgReportW(rptType, SIMP_WIDE(__FILE__), __LINE__, 0, fmt, __VA_ARGS__)) || \
    (_CrtDbgBreak(), 0))

// _TCHAR 版
#ifdef _UNICODE
#define SIMP_RPT    SIMP_RPTW
#define SIMP_RPTF   SIMP_RPTFW
#else
#define SIMP_RPT    SIMP_RPTA
#define SIMP_RPTF   SIMP_RPTFA
#endif

//
////////////////////////////////////////////////////////////////////////////////

// 调用函数 func(paramList), 并用 SIMP_RPT 输出其返回值
//
// [要求]
//   1. paramList 用括号包起来, 如 (p1, p2)
//   2. func 的返回值是整数类型, 如 表示函数执行结果的状态值, 错误码
#define SIMP_CALL_RPT(rptType, prefix, ret, func, paramList) { \
        ret = func##paramList; \
        SIMP_RPT(rptType, prefix _T("%s: return=%d\n"), SIMP_STRINGIZET(func), ret); \
    }

////////////////////////////////////////////////////////////////////////////////
// Assert 断言
// 接受任意个数参数的 Assert
// 使用 !!, 而不使用 expr 的比较运算符 (operator==), 后者可能因为重载而出问题, 影响 || 后面的语句
//

// char 版
#define SIMP_ASSERTEA(expr, fmt, ...) \
    (void) ((!!(expr)) || \
    (1 != _CrtDbgReport(_CRT_ASSERT, __FILE__, __LINE__, 0, fmt, __VA_ARGS__)) || \
    (_CrtDbgBreak(), 0))

// wchar_t 版
#define SIMP_ASSERTEW(expr, fmt, ...) \
    (void) ((!!(expr)) || \
    (1 != _CrtDbgReportW(_CRT_ASSERT, SIMP_WIDE(__FILE__), __LINE__, 0, fmt, __VA_ARGS__)) || \
    (_CrtDbgBreak(), 0))

// _TCHAR 版
#ifdef _UNICODE
#define SIMP_ASSERT SIMP_ASSERTEW
#else
#define SIMP_ASSERT SIMP_ASSERTEA
#endif

//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// 诊断一段内存是否能够读写
// 能够访问时产生 SIMP_RPT 调试输出, 不能访问时产生 Assert
//

#define SIMP_MEMORY_READ            0
#define SIMP_MEMORY_READ_WRITE      1
#define SIMP_MEMORY_ACCESS_MODES    2

// NOTE:
// _CrtIsValidPointer 只在 Debug 配置下定义
// VC 2005 中 _CrtIsValidPointer 实现只是简单判断一下地址是否为 0, 并没有
// 检查地址空间和内存区段, 传入的地址长度 size 和访问方式 access 都没有用

#define SIMP_ASSERT_MEMORY(rptType, prefix, addr, Size, access) { \
        if (access != SIMP_MEMORY_READ && access != SIMP_MEMORY_READ_WRITE) \
            SIMP_RPT(_CRT_ERROR, prefix _T("can't support such memory access method\n")); \
        else { \
            if (_CrtIsValidPointer(addr, (unsigned int) Size, access)) \
                SIMP_RPT(rptType, prefix _T("access memory passed: addr=0x%08X, size=%d, access=%s\n"), \
                           addr, Size, (access == SIMP_MEMORY_READ ? _T("read") : _T("read write"))); \
            else \
                SIMP_ASSERT_EXPR(0, _T("\n") prefix _T("access memory failed: addr=0x%08X, size=%d, access=%s\n"), \
                                 addr, Size, (access == SIMP_MEMORY_READ ? _T("read") : _T("read write"))); \
        } \
    }

//
////////////////////////////////////////////////////////////////////////////////

#define SIMP_DEBUG_ONLY(expr)   expr    // 只在 Debug 版有效的语句
#define SIMP_RELEASE_ONLY(expr) 0       // 只在 Release 版有效的语句

#else
// _DEBUG NOT defined

#define SIMP_RPTA(rptType, fmt, ...)    0
#define SIMP_RPTFA(rptType, fmt, ...)   0
#define SIMP_RPTW(rptType, fmt, ...)    0
#define SIMP_RPTFW(rptType, fmt, ...)   0
#define SIMP_RPT(rptType, fmt, ...)     0
#define SIMP_RPTF(rptType, fmt, ...)    0

#define SIMP_CALL_RPT(rptType, prefix, ret, func, paramList)    0

#define SIMP_ASSERT_EXPR(expr, fmt, ...)                        0

#define SIMP_ASSERT_MEMORY(rptType, prefix, addr, Size, access) 0

#define SIMP_DEBUG_ONLY(expr)       0
#define SIMP_RELEASE_ONLY(expr)     expr
#endif

// 以 "模块名!函数名:" 形式输出调试报告
#define SIMP_RPTFMT(module, fmt)    _T(module) _T("!") _T(__FUNCTION__) _T(": ")  _T(fmt) _T("\n")
#define SIMP_RPTFMTA(module, fmt)   module "!" __FUNCTION__ ": " fmt "\n"

#define SIMP_FMTRPT(module, rptType, fmt, ...)  SIMP_RPT(rptType, SIMP_RPTFMT(module, fmt), __VA_ARGS__)
#define SIMP_FMTRPTA(module, rptType, fmt, ...) SIMP_RPTA(rptType, SIMP_RPTFMTA(module, fmt), __VA_ARGS__)

////////////////////////////////////////////////////////////////////////////////
// Windows API 调试输出
////////////////////////////////////////////////////////////////////////////////

// 转接 Windows API OutputDebugString 的函数模板, 无一般化定义
template <typename CharT>
void OutputDebug(const CharT* str);

// OutputDebug 的 char 特化
template <>
inline
void OutputDebug(const char* str) {
    OutputDebugStringA(str);
}

// OutputDebug 的 wchar_t 特化
template <>
inline
void OutputDebug(const wchar_t* str) {
    OutputDebugStringW(str);
}

SIMP_NS_END
