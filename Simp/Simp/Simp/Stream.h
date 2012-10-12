////////////////////////////////////////////////////////////////////////////////
// 文    件 : Stream.h
// 功能说明 :
//   std 流辅助功能
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
// _TCHAR 字符类型的 std 流类型定义
////////////////////////////////////////////////////////////////////////////////

typedef std::basic_ios<_TCHAR, std::char_traits<_TCHAR> >                                   tios;
typedef std::basic_streambuf<_TCHAR, std::char_traits<_TCHAR> >                             tstreambuf;
typedef std::basic_istream<_TCHAR, std::char_traits<_TCHAR> >                               tistream;
typedef std::basic_ostream<_TCHAR, std::char_traits<_TCHAR> >                               tostream;
typedef std::basic_iostream<_TCHAR, std::char_traits<_TCHAR> >                              tiostream;
typedef std::basic_stringbuf<_TCHAR, std::char_traits<_TCHAR>, std::allocator<_TCHAR> >     tstringbuf;
typedef std::basic_istringstream<_TCHAR, std::char_traits<_TCHAR>, std::allocator<_TCHAR> > tistringstream;
typedef std::basic_ostringstream<_TCHAR, std::char_traits<_TCHAR>, std::allocator<_TCHAR> > tostringstream;
typedef std::basic_stringstream<_TCHAR, std::char_traits<_TCHAR>, std::allocator<_TCHAR> >  tstringstream;
typedef std::basic_filebuf<_TCHAR, std::char_traits<_TCHAR> >                               tfilebuf;
typedef std::basic_ifstream<_TCHAR, std::char_traits<_TCHAR> >                              tifstream;
typedef std::basic_ofstream<_TCHAR, std::char_traits<_TCHAR> >                              tofstream;
typedef std::basic_fstream<_TCHAR, std::char_traits<_TCHAR> >                               tfstream;

////////////////////////////////////////////////////////////////////////////////
// _TCHAR 字符类型的 std 流全局变量
////////////////////////////////////////////////////////////////////////////////

// NOTE:
// 1. 使用引用类型, 它不创建对象, 只是 std 中标准对象的别名
// 2. 使用 static 内部链接方式, 以便在 .h 文件中定义, 而不仅是声明全局变量, 即 header-only
//    因为全局变量默认使用外部链接方式, 多个 .cpp 包含该 .h 后会因多次定义, 导致链接错误 LNK2005

#ifdef _UNICODE
static std::wistream& tcin  = std::wcin;
static std::wostream& tcout = std::wcout;
static std::wostream& tcerr = std::wcerr;
static std::wostream& tclog = std::wclog;
#else
// _UNICODE NOT defined
static std::istream& tcin   = std::cin;
static std::ostream& tcout  = std::cout;
static std::ostream& tcerr  = std::cerr;
static std::ostream& tclog  = std::clog;
#endif

SIMP_NS_END
