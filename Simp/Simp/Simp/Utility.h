////////////////////////////////////////////////////////////////////////////////
// 文    件 : Utility.h
// 功能说明 :
//   实用工具
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
// 最值
////////////////////////////////////////////////////////////////////////////////

template <typename Type>
inline
const Type& Min(const Type& l, const Type& r) {
    return (l < r ? l : r);
}

template <typename Type>
inline
const Type& Max(const Type& l, const Type& r) {
    return (l > r ? l : r);
}

// [要求]
//   Type 有操作 operator>
//   minv, maxv 和 l, r 是不同对象
template <typename Type>
inline
void MinMax(const Type& l, const Type& r, __out Type& minv, __out Type& maxv) {
    if (l > r) {
        minv = r;
        maxv = l;
    }
    else {
        minv = l;
        maxv = r;
    }
}

// 比较左操作数 lmin 和右操作数 rmax 的大小
// 将小的交换存储到 lmin, 大的存储到 rmax
// [要求]
//   两个操作数都必需是左值
//   Type 有可访问的拷贝构造函数
//   Type 有操作 operator>
//   Type 有操作 operator=
template <typename Type>
inline
void MinMax(__inout Type& lmin, __inout Type& rmax) {
    if (lmin > rmax)
        std::swap(lmin, rmax);
}

SIMP_NS_END
