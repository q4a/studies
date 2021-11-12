////////////////////////////////////////////////////////////////////////////////
// FILE         : string.cpp
// DESCRIPTION  :
//   字符串 class String 示例
//   改自 "C++ Programming Language, Special Ed" 11.12 A String Class
//   技术: pimpl, RC, COW, Proxy class
//   功能: 值语义的 string 类示例, 没有模板化之 CharType、CharTraits 和 Allocator
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

namespace breaker {

typedef std::out_of_range RangeError;

////////////////////////////////////////////////////////////////////////////////
// class String 的内部表示 class StrRep (Representation)
////////////////////////////////////////////////////////////////////////////////

class StrRep : private boost::noncopyable {
    friend class String;
private:
    struct Attach {};
    static const Attach Attached;

    StrRep(size_t sz, char* str, const Attach& attach) : refCnt_(1), size_(sz), str_(str) {}

    StrRep(size_t sz, const char* str) : refCnt_(1), size_(sz) {
        str_ = new char[sz + 1];
        strcpy_s(str_, sz + 1, str);
    }

    ~StrRep() {
        delete[] str_;
    }

    // 意思是 get own OR copy, 根据 refCnt_ == 1, 得到本体或其拷贝
    StrRep* get_own_copy() {
        if (refCnt_ == 1)
            return this;
        --refCnt_;
        return new StrRep(size_, str_);
    }

    void assign(size_t sz, const char* str) {
        if (sz == size_) {  // sz == size_ 时, 复用缓冲区 str_
            strcpy_s(str_, sz + 1, str);
            return;
        }
        str_ = alloc<TRUE, TRUE>(sz + 1);
        size_ = sz;
    }

    void append(size_t sz, const char* str) {
        if (sz == 0)
            return;
        size_t newsz = size_ + sz;
        str_ = alloc<TRUE, TRUE>(newsz + 1);
        strcpy_s(str_ + size_, sz + 1, str);
        size_ = newsz;
    }

    StrRep* copy_append(size_t sz, const char* str) {
        if (sz == 0)
            return this;
        size_t newsz = size_ + sz;
        char* newstr = alloc<TRUE, FALSE>(newsz + 1);
        strcpy_s(newstr + size_, sz + 1, str);
        return new StrRep(newsz, newstr, Attached);
    }

    template <BOOL CopyOld, BOOL DelOld>
    char* alloc(size_t sz) {
        char* newstr = new char[sz];
        if (CopyOld)
            strcpy_s(newstr, sz, str_);
        if (DelOld)
            delete[] str_;
        return newstr;
    }

    UINT    refCnt_;
    char*   str_;
    size_t  size_;  // 字符个数, 不包括结尾 0
};

const StrRep::Attach StrRep::Attached;

////////////////////////////////////////////////////////////////////////////////
// char& 的 Proxy class CharRef
////////////////////////////////////////////////////////////////////////////////

// class CharRef: 用以区分 String::operator[] 的读 (右值使用 R-value Usage) 和写 (左值使用 L-value Usage)

class CharRef {
    friend class String;
private:
    CharRef(String& str, size_t i) : str_(str), idx_(i) {}

public:
    inline operator char() const;
    inline void operator=(char c);

private:
    String& str_;
    size_t  idx_;
};

////////////////////////////////////////////////////////////////////////////////
// 字符串 class String
////////////////////////////////////////////////////////////////////////////////

class String {
public:
    String() : rep_(new StrRep(0, "")) {}

    String(const char* str) : rep_(new StrRep(strlen(str), str)) {}

    String(const char* str1, const char* str2) {
        size_t sz1 = strlen(str1);
        size_t sz2 = strlen(str2);
        char* newstr = new char[sz1 + sz2 + 1];
        strcpy_s(newstr, sz1 + 1, str1);
        strcpy_s(newstr + sz1, sz2 + 1, str2);
        rep_ = new StrRep(sz1 + sz2, newstr, StrRep::Attached);
    }

    String(const String& r) : rep_(r.rep_) {
        r.rep_->refCnt_++;
    }

    ~String() {
        if (--rep_->refCnt_ == 0)
            delete rep_;
    }

    String& operator=(const char* str) {
        if (rep_->refCnt_ == 1)
            rep_->assign(strlen(str), str);         // 重用 StrRep
        else {
            rep_->refCnt_--;
            rep_ = new StrRep(strlen(str), str);    // 拷贝 StrRep
        }
        return *this;
    }

    String& operator=(const String& r) {
        r.rep_->refCnt_++;  // 先增加计数, 防止自赋值引起下句释放 StrRep
        if (--rep_->refCnt_ == 0)
            delete rep_;
        rep_ = r.rep_;
        return *this;
    }

    char read(size_t i) const {
        return rep_->str_[i];
    }

    void write(size_t i, char c) {
        rep_ = rep_->get_own_copy();
        rep_->str_[i] = c;
    }

    // 左值使用的 [], 通过 CharRef::operator= 作用
    // 右值使用的 [], 通过 CharRef::operator char 作用
    CharRef operator[](size_t i) {
        return CharRef(*this, i);
    }

    // 右值使用的 [], 本体 const
    char operator[](size_t i) const {
        return rep_->str_[i];
    }

    // 左值和右值使用的 at, 带范围检查
    CharRef at(size_t i) {
        check(i);
        return CharRef(*this, i);
    }

    // 右值使用的 at, 带范围检查, 本体 const
    char at(size_t i) const {
        check(i);
        return rep_->str_[i];
    }

    size_t size() const {
        return rep_->size_;
    }

    void check(size_t i) const {
        if (i >= rep_->size_)
            throw RangeError("index in String is out of range");
    }

    std::ostream& output(std::ostream& os) const {
        os << rep_->str_;
        return os;
    }

    const char* c_str() const {
        return rep_->str_;
    }

    String& operator+=(const char* str) {
        if (rep_->refCnt_ == 1)
            rep_->append(strlen(str), str);             // 重用 StrRep
        else {
            rep_->refCnt_--;
            rep_ = rep_->copy_append(strlen(str), str); // 拷贝 StrRep
        }
        return *this;
    }

    String& operator+=(const String& r) {
        return ((*this) += r.rep_->str_);
    }

private:
    StrRep* rep_;
};

////////////////////////////////////////////////////////////////////////////////
// class CharRef 成员
////////////////////////////////////////////////////////////////////////////////

// 读字符, 右值使用 R-value Usage
CharRef::operator char() const
{
    return str_.read(idx_);
}

// 写字符, 左值使用 L-value Usage
void CharRef::operator=(char c)
{
    str_.write(idx_, c);
}

////////////////////////////////////////////////////////////////////////////////
// class String 辅助函数
////////////////////////////////////////////////////////////////////////////////

inline std::ostream& operator<<(std::ostream& os, const String& str)
{
    return str.output(os);
}

inline BOOL operator==(const String& l, const String& r)
{
    return !strcmp(l.c_str(), r.c_str());
}

inline BOOL operator!=(const String& l, const String& r)
{
    return strcmp(l.c_str(), r.c_str());
}

inline const String operator+(const String& l, const String& r)
{
    return String(l.c_str(), r.c_str());    // RVO
}

}   // namespace breaker
