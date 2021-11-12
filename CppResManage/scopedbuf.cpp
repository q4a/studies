////////////////////////////////////////////////////////////////////////////////
// FILE         : scopedbuf.cpp
// DESCRIPTION  :
//   scoped �ͻ����� class ScopedBuf
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
// CRT �ڴ������ class Malloc
////////////////////////////////////////////////////////////////////////////////

// CRT �ڴ���亯�� malloc ��ǳ��װ��������

template <class _Type, BOOL ThrowExcept = TRUE>
class Malloc {
public:
    typedef _Type   Type;
    typedef _Type*  TypePtr;
    typedef _Type&  TypeRef;

    Malloc() {}

    // cnt �� Type ����, ������ byte ��
    TypePtr alloc(size_t cnt) {
        TypePtr p = (TypePtr) ::malloc(cnt * sizeof(Type));
        if (ThrowExcept && p == NULL)
            throw std::bad_alloc();
        return p;
    }

    // realloc �� CRT ��ռ��, ������ realloca
    TypePtr realloca(TypePtr ptr, size_t cnt) {
        TypePtr p = (TypePtr) ::realloc(ptr, cnt * sizeof(Type));
        if (ThrowExcept && p == NULL && cnt != 0)
            throw std::bad_alloc();
        return p;
    }

    void dealloc(TypePtr ptr) {
        ::free(ptr);
    }

    // �� ptr ������ val ֵ, ����ʽ new
    void construct(TypePtr ptr, const Type& val) {
        new(ptr) Type(val);
    }

    // ���� Type ����, �����ͷŶ�����Ĵ洢
    void destroy(TypePtr ptr) {
        ptr->~Type();
    }
};

////////////////////////////////////////////////////////////////////////////////
// scoped �ͻ����� class ScopedBuf
////////////////////////////////////////////////////////////////////////////////

// scoped �ͻ����� class ScopedBuf (Monopolize ����)

template <class _Type, class Alloc = Malloc<_Type, TRUE> >
class ScopedBuf : private boost::noncopyable {
public:
    typedef _Type   Type;

    ScopedBuf(Alloc ac = Alloc()) : buf_(NULL), cnt_(0), ac_(ac) {}

    // cnt �� Type ����, ������ byte ��
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
    // �����ڴ�
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

    // ���·����ڴ�
    void realloca(size_t cnt) {
        cnt_ = cnt;
        buf_ = ac_.realloca(buf_, cnt);
    }

    // ��չ�ڴ�
    void expand(double ratio) {
        return realloca(cnt_ + (size_t) (cnt_ * ratio));
    }
    void expand() {
        return realloca(cnt_ + (cnt_ >> 1));
    }

    // �ͷ��ڴ�
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

    // �±����
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

    // buf �����Ƿ����� Alloc ����Ĵ洢
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
