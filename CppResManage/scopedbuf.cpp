////////////////////////////////////////////////////////////////////////////////
// FILE         : scopedbuf.cpp
// DESCRIPTION  :
//   scoped 型缓冲区 class ScopedBuf
//   use vector and resize to expand buffer instead.
//
// AUTHOR       : Breaker Zhao <breaker.zy_AT_gmail>
// DATE         : 2011-10
// LICENSE      : Microsoft Public License <http://www.microsoft.com/en-us/openness/licenses.aspx#MPL>
//
// DISCLAIMER   :
//   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
//   EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
//   WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CRT 内存分配器 class Malloc
////////////////////////////////////////////////////////////////////////////////

// CRT 内存分配函数 malloc 的浅封装分配器类

template <class _Type, BOOL ThrowExcept = TRUE>
class Malloc {
public:
    typedef _Type   Type;
    typedef _Type*  TypePtr;
    typedef _Type&  TypeRef;

    Malloc() {}

    // cnt 是 Type 个数, 而不是 byte 数
    TypePtr alloc(size_t cnt) {
        TypePtr p = (TypePtr) ::malloc(cnt * sizeof(Type));
        if (ThrowExcept && p == NULL)
            throw std::bad_alloc();
        return p;
    }

    // realloc 被 CRT 宏占用, 所以用 realloca
    TypePtr realloca(TypePtr ptr, size_t cnt) {
        TypePtr p = (TypePtr) ::realloc(ptr, cnt * sizeof(Type));
        if (ThrowExcept && p == NULL && cnt != 0)
            throw std::bad_alloc();
        return p;
    }

    void dealloc(TypePtr ptr) {
        ::free(ptr);
    }

    // 在 ptr 处构造 val 值, 放置式 new
    void construct(TypePtr ptr, const Type& val) {
        new(ptr) Type(val);
    }

    // 析构 Type 对象, 但不释放对象本身的存储
    void destroy(TypePtr ptr) {
        ptr->~Type();
    }
};

////////////////////////////////////////////////////////////////////////////////
// scoped 型缓冲区 class ScopedBuf
////////////////////////////////////////////////////////////////////////////////

// scoped 型缓冲区 class ScopedBuf (Monopolize 语义)

template <class _Type, class Alloc = Malloc<_Type, TRUE> >
class ScopedBuf : private boost::noncopyable {
public:
    typedef _Type   Type;

    ScopedBuf(Alloc ac = Alloc()) : buf_(NULL), cnt_(0), ac_(ac) {}

    // cnt 是 Type 个数, 而不是 byte 数
    ScopedBuf(size_t cnt, Alloc ac = Alloc()) : ac_(ac) {
        alloc(cnt);
    }

    ScopedBuf(size_t cnt, const Type& val, Alloc ac = Alloc()) : ac_(ac) {
        alloc(cnt);
        for (size_t i = 0; i < cnt; ++i)
            ac.construct(buf_ + i, val);
    }

    ~ScopedBuf() {
        for (size_t i = 0; i < cnt_; ++i)
            ac_.destroy(buf_ + i);
        dealloc();
    }

public:
    // 分配内存
    template <BOOL Check>
    void alloc(size_t cnt) {
        if (Check && buf_ != NULL)
            dealloc();
        cnt_ = cnt;
        buf_ = ac_.alloc(cnt);
    }

    void alloc(size_t cnt) {
        return alloc<FALSE>(cnt);
    }

    void alloc_c(size_t cnt) {
        return alloc<TRUE>(cnt);
    }

    // 重新分配内存
    void realloca(size_t cnt) {
        cnt_ = cnt;
        buf_ = ac_.realloca(buf_, cnt);
    }

    // 扩展内存
    void expand(double ratio) {
        return realloca(cnt_ + (size_t) (cnt_ * ratio));
    }
    void expand() {
        return realloca(cnt_ + (cnt_ >> 1));
    }

    // 释放内存
    void dealloc() {
        ac_.dealloc(buf_);
        buf_ = NULL;
        cnt_ = 0;
    }

    size_t size() const {
        return cnt_;
    }

    Type* buf() {
        return buf_;
    }

    // 下标操作
    Type& operator[](size_t idx) {
        return buf_[idx];
    }
    Type& at(size_t idx) {
        if (buf_ == NULL)
            throw std::exception("Null Pointer");
        if (idx >= cnt_)
            throw std::exception("Error Range");
        return buf_[idx];
    }

    Type* detach() {
        Type* p = buf_;
        buf_ = NULL;
        cnt_ = 0;
        return p;
    }

    // buf 必需是分配器 Alloc 分配的存储
    void attach(Type* buf, size_t cnt) {
        if (buf_ != NULL)
            ac_.dealloc(buf_);
        buf_ = buf;
        cnt_ = cnt;
    }

private:
    Type*   buf_;
    size_t  cnt_;
    Alloc   ac_;
};
