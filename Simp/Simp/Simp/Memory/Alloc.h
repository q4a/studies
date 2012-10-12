////////////////////////////////////////////////////////////////////////////////
// 文    件 : Alloc.h
// 功能说明 :
//   内存分配
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
// 内存分配函数
////////////////////////////////////////////////////////////////////////////////

// Simp 的通用内存分配函数, 默认转接到 CRT 的 malloc/free
// Simp 内部均使用下列分配函数, 可在用户程序中定义 SIMP_OVERRIDE_ALLOC 以覆盖下列分配函数

#ifndef SIMP_OVERRIDE_ALLOC

inline
void* Malloc(size_t size) {
    return malloc(size);
}

inline
void* Realloc(void* memblock, size_t size) {
    return realloc(memblock, size);
}

inline
void* Calloc(size_t num, size_t size) {
    return calloc(num, size);
}

inline
void Free(void* memblock) {
    free(memblock);
}

#endif  // SIMP_OVERRIDE_ALLOC NOT defined

////////////////////////////////////////////////////////////////////////////////
// 内存分配器类 Mallocator
////////////////////////////////////////////////////////////////////////////////

// 基于 Malloc 的分配器类
template <typename _Type, BOOL ThrowExcept = FALSE>
class Mallocator {
public:
    typedef _Type Type;

    Mallocator() {}

    // count 是 Type 个数, 而不是 byte 数
    Type* Alloc(size_t count) {
        Type* p = (Type*) Malloc(count * sizeof(Type));
        if (ThrowExcept && p == NULL)
            throw std::bad_alloc(__FUNCTION__ " failed");
        return p;
    }

    Type* Realloc(Type* p, size_t count) {
        Type* q = (Type*) Simp::Realloc(p, count * sizeof(Type));
        if (ThrowExcept && q == NULL && count != 0)
            throw std::bad_alloc(__FUNCTION__ " failed");
        return q;
    }

    void Free(Type* p) {
        Simp::Free(p);
    }

    // 在 p 处构造 val 值, 放置式 new
    void Construct(Type* p, const Type& val) {
        new(p) Type(val);
    }

    // 析构 Type 对象, 但不释放对象本身的存储
    void Destroy(Type* p) {
        p->~Type();
    }
};

SIMP_NS_END
