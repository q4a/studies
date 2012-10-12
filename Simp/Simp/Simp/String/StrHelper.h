////////////////////////////////////////////////////////////////////////////////
// 文    件 : StrHelper.h
// 功能说明 :
//   字符串常用操作
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

////////////////////////////////////////////////////////////////////////////////
// 类型定义
////////////////////////////////////////////////////////////////////////////////

typedef std::basic_string<_TCHAR> tstring;

////////////////////////////////////////////////////////////////////////////////
// 字符特征类 CharTraits
////////////////////////////////////////////////////////////////////////////////

template <typename CharT>
struct CharTraits {
    typedef CharT   CharType;
    typedef int     IntType;
    static const IntType XEOF = -1;
};

// char 特化
template <>
struct CharTraits<char> {
    typedef char    CharType;
    typedef int     IntType;
    static const IntType XEOF = EOF;
};

// wchar_t 特化
template <>
struct CharTraits<wchar_t> {
    typedef wchar_t CharType;
    typedef wint_t  IntType;
    static const IntType XEOF = WEOF;
};

////////////////////////////////////////////////////////////////////////////////
// 字符串格式化函数
////////////////////////////////////////////////////////////////////////////////

// 转接 CRT vsprintf 的函数模板, 无一般化定义
template <typename CharT>
int vsprintf_t(CharT* buf, size_t charSize, const CharT* format, va_list args);

// vsprintf_t 的 char 特化
template <>
inline
int vsprintf_t(char* buf, size_t charSize, const char* format, va_list args) {
    return vsprintf_s(buf, charSize, format, args);
}

// vsprintf_t 的 wchar_t 特化
template <>
inline
int vsprintf_t(wchar_t* buf, size_t charSize, const wchar_t* format, va_list args) {
    return vswprintf_s(buf, charSize, format, args);
}

// 格式化构造 string
template <size_t BufSize, typename CharT>
inline
std::basic_string<CharT> MakeString(const CharT* format, ...) {
    CharT buf[BufSize];
    va_list args;
    va_start(args, format);
    vsprintf_t(buf, BufSize, format, args);
    va_end(args);
    return std::basic_string<CharT>(buf);
}

SIMP_NS_END
