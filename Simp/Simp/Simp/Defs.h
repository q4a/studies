////////////////////////////////////////////////////////////////////////////////
// 文    件 : Defs.h
// 功能说明 :
//   基本类型和功能
//
// 版    本 : 1.0
// 作    者 : Breaker Zhao <breaker.zy_AT_gmail>
// 日    期 : 2011-10
// 授权许可 : Microsoft Public License <http://www.microsoft.com/en-us/openness/licenses.aspx#MPL>
////////////////////////////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////////////////////////////
// Simp 库的名字空间
////////////////////////////////////////////////////////////////////////////////

#define SIMP_NS_BEGIN   namespace Simp {
#define SIMP_NS_END     }

SIMP_NS_BEGIN

////////////////////////////////////////////////////////////////////////////////
// Simp 库的版本
////////////////////////////////////////////////////////////////////////////////

#define SIMP_VER        0x01000001
#define SIMP_VER_STR    "1.0.0.1"

////////////////////////////////////////////////////////////////////////////////
// 辅助功能
////////////////////////////////////////////////////////////////////////////////

// 注释没使用过变量或参数
#define SIMP_NOT_USED(x)        (x)

// 字符串化字面量
#define _SIMP_STRINGIZE(x)      #x
#define SIMP_STRINGIZE(x)       _SIMP_STRINGIZE(x)
#define SIMP_STRINGIZET(x)      _T(SIMP_STRINGIZE(x))

// 拼接
#define _SIMP_CONCAT(x, y)      x##y
#define SIMP_CONCAT(x, y)       _SIMP_CONCAT(x, y)

// 宽化字符串字面量
#define _SIMP_WIDE(str)         L##str
#define SIMP_WIDE(str)          _SIMP_WIDE(str)

// C/C++ 链接约定
#ifdef __cplusplus
#define SIMP_EXTERN_C           extern "C"
#define SIMP_EXTERN_C_BEGIN     extern "C" {
#define SIMP_EXTERN_C_END       }
#define SIMP_EXTERN_CPP         extern "C++"
#define SIMP_EXTERN_CPP_BEGIN   extern "C++" {
#define SIMP_EXTERN_CPP_END     }
#else
// __cplusplus NOT defined
#define SIMP_EXTERN_C           extern
#define SIMP_EXTERN_C_BEGIN
#define SIMP_EXTERN_C_END
#endif

// 只产生一个全局存储, 以便在 .h 中定义全局变量
#define SIMP_GLOBAL __declspec(selectany)

// 如果 TRUE 就去做
#define SIMP_TRUE_DO(x, exp)    if (x) { exp; }
#define SIMP_ON_DO(x, exp)      SIMP_TRUE_DO((x), exp)
// 如果 FALSE 就去做
#define SIMP_FALSE_DO(x, exp)   if (!(x)) { exp; }
#define SIMP_OFF_DO(x, exp)     SIMP_FALSE_DO((x), exp)

// 做完某事后 goto
#define SIMP_GOTO(exp, label)   { exp; goto label; }

// 掩码值
// 32bit 掩码值的整数 x 有效取值 0 ~ 31
// x86 GCC 和 VC 实现中 SIMP_MASK(0) = SIMP_MASK(32) = 1
#define SIMP_MASK(x)            (1 << (x))

// Simp 模块名
const char      MODULE_NAMEA[]  = "Simp";
const wchar_t   MODULE_NAMEW[]  = L"Simp";
const _TCHAR    MODULE_NAME[]   = _T("Simp");

////////////////////////////////////////////////////////////////////////////////
// 静态断言
////////////////////////////////////////////////////////////////////////////////

// 如果 expr = FALSE, VC 产生编译错误 error C2027
template <BOOL expr> struct StaticAssert;
template <> struct StaticAssert<TRUE> {};
template <size_t Size> struct StaticAssertTest {};

#define SIMP_STATIC_ASSERT(x) \
    typedef StaticAssertTest<sizeof(StaticAssert<BOOL(x)>)> StaticAssertType##__LINE__

////////////////////////////////////////////////////////////////////////////////
// 内存分配函数
////////////////////////////////////////////////////////////////////////////////

// Simp 的通用内存分配函数, 在 memory/alloc.h 中定义

extern void* Malloc(size_t size);
extern void* Realloc(void* memblock, size_t size);
extern void* Calloc(size_t num, size_t size);
extern void Free(void* memblock);

SIMP_NS_END
