////////////////////////////////////////////////////////////////////////////////
// 文    件 : Singleton.h
// 功能说明 :
//   单件模式类
//
// 版    本 : 1.0
// 作    者 : Breaker Zhao <breaker.zy_AT_gmail>
// 日    期 : 2011-10
// 授权许可 : Microsoft Public License <http://www.microsoft.com/en-us/openness/licenses.aspx#MPL>
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <Simp/Depends.h>
#include <Simp/Defs.h>

#include <Simp/Pattern/Uncopyable.h>

SIMP_NS_BEGIN

////////////////////////////////////////////////////////////////////////////////
// 单件类模板 Singleton
////////////////////////////////////////////////////////////////////////////////

// 简单的单件类, 使用局部静态存储, 不能提前释放 (程序结束前), 第一次初始化有线程安全问题
//
// [要求]
//   用户类型 Type 有可访问的默认构造函数
template <typename _Type>
struct Singleton : private Uncopyable {
    typedef _Type Type;

    static Type& Inst() {
        static Type obj;
        return obj;
    }
};

SIMP_NS_END
