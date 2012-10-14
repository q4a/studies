////////////////////////////////////////////////////////////////////////////////
// 文    件 : SmartPtr.h
// 功能说明 :
//   智能指针
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
#include <Simp/Memory/MemHelper.h>
#include <Simp/Memory/Alloc.h>

SIMP_NS_BEGIN

////////////////////////////////////////////////////////////////////////////////
// Auto 型智能指针 AutoPtr
////////////////////////////////////////////////////////////////////////////////

// 可指定 deleter 的 Auto 型智能指针 (Transfer 语义)
template <typename _Type, typename _Deleter = StdDel<FALSE, FALSE> >
class AutoPtr {
public:
    typedef _Type Type;
    typedef _Deleter Deleter;

    explicit AutoPtr(Type* p = NULL, Deleter del = Deleter()) : m_Obj(p), m_Del(del) {}

    // Transfer 语义的 copy ctor
    AutoPtr(AutoPtr& right) : m_Obj(right.Release()) {}

    // 可转换类型 (继承格) 间的 copy ctor
    template <typename TR>
    AutoPtr(AutoPtr<TR>& right) : m_Obj(right.Release()) {}

    ~AutoPtr() {
        m_Del(m_Obj);
    }

    // Transfer 语义的 assign
    AutoPtr& operator=(AutoPtr& right) {
        if (&right != this) {
            m_Del(m_Obj);
            m_Obj = right.Release();
        }
        return *this;
    }

    // 可转换类型 (继承格) 间的 assign
    template <typename TR>
    AutoPtr& operator=(AutoPtr<TR>& right) {
        if (right.Get() != m_Obj) {
            m_Del(m_Obj);
            m_Obj = right.Release();
        }
        return *this;
    }

    Type* Get() const {
        return m_Obj;
    }

    Type* operator->() const {
        return m_Obj;
    }

    Type& operator*() const {
        return *m_Obj;
    }

    // 取消托管, 返回之前的托管对象
    Type* Release() {
        Type* p = m_Obj;
        m_Obj = NULL;
        return p;
    }

    // 重置托管对象
    void Reset(Type* p = NULL) {
        m_Del(m_Obj);
        m_Obj = p;
    }

private:
    Type*   m_Obj;
    Deleter m_Del;
};

////////////////////////////////////////////////////////////////////////////////
// Auto 型智能指针 AutoArr
////////////////////////////////////////////////////////////////////////////////

// AutoPtr 的数组版
template <typename Type, typename Deleter = StdDelArr<FALSE, FALSE> >
class AutoArr : public AutoPtr<Type, Deleter> {
public:
    explicit AutoArr(Type* p = NULL, Deleter del = Deleter()) : AutoPtr(p, del) {}

    // 不检查下标和托管对象的有效性, 以保证效率
    Type& operator[](size_t idx) {
        return Get()[idx];
    }
};

////////////////////////////////////////////////////////////////////////////////
// Scoped 型缓冲区类 ScopedBuf
////////////////////////////////////////////////////////////////////////////////

// Scoped 型缓冲区类 (Monopolize 语义)
template <typename _Type, typename _Allocator = Mallocator<_Type, TRUE> >
class ScopedBuf : private Uncopyable {
public:
    typedef _Type Type;
    typedef _Allocator Allocator;

    ScopedBuf(Allocator ac = Allocator()) : m_Buf(NULL), m_Size(0), m_Alloc(ac) {}

    // sz 是 Type 个数, 而不是 byte 数
    ScopedBuf(size_t sz, Allocator ac = Allocator()) : m_Alloc(ac) {
        Alloc(sz);
    }

    ScopedBuf(size_t sz, const Type& val, Allocator ac = Allocator()) : m_Alloc(ac) {
        Alloc(sz);
        for (size_t i = 0; i < sz; ++i)
            ac.Construct(m_Buf + i, val);
    }

    ~ScopedBuf() {
        for (size_t i = 0; i < m_Size; ++i)
            m_Alloc.Destroy(m_Buf + i);
        Free();
    }

public:
    // 分配内存
    template <BOOL Check>
    void Alloc(size_t sz) {
        if (Check && m_Buf != NULL)
            Free();
        m_Size = sz;
        m_Buf = m_Alloc.Alloc(sz);
    }

    void Alloc(size_t sz) {
        return Alloc<FALSE>(sz);
    }

    void AllocCheckFree(size_t sz) {
        return Alloc<TRUE>(sz);
    }

    // 重新分配内存
    void Realloc(size_t sz) {
        m_Size = sz;
        m_Buf = m_Alloc.Realloc(m_Buf, sz);
    }

    // 扩展内存
    void Expand(double ratio) {
        return Realloc(m_Size + (size_t) (m_Size * Max(ratio, MIN_REALLOCRATIO)));
    }
    void Expand() {
        return Realloc(m_Size + (m_Size >> 1));
    }

    // 释放内存
    void Free() {
        m_Alloc.Free(m_Buf);
        m_Buf = NULL;
        m_Size = 0;
    }

    size_t Size() const {
        return m_Size;
    }

    Type* Buf() {
        return m_Buf;
    }

    // 下标操作
    Type& operator[](size_t idx) {
        return At(idx);
    }
    Type& At(size_t idx) {
        _ASSERTE(m_Buf != NULL);
        _ASSERTE(idx < m_Size);
        return m_Buf[idx];
    }

    Type* Detach() {
        Type* p = m_Buf;
        m_Buf = NULL;
        m_Size = 0;
        return p;
    }

    // buf 必需是分配器 Allocator 分配的存储
    void Attach(Type* buf, size_t sz) {
        if (m_Buf != NULL)
            m_Alloc.Free(m_Buf);
        m_Buf = buf;
        m_Size = sz;
    }

public:
    static const double MIN_REALLOCRATIO;

private:
    Type*       m_Buf;
    size_t      m_Size;
    Allocator   m_Alloc;
};

template <typename _Type, typename _Allocator>
const double ScopedBuf<_Type, _Allocator>::MIN_REALLOCRATIO = 0.01;

SIMP_NS_END
