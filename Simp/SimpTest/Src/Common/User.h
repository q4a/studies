// User.h
//

#pragma once

////////////////////////////////////////////////////////////////////////////////
// 用户类 User
////////////////////////////////////////////////////////////////////////////////

class User {
public:
    // ctor
    User(const Simp::tstring& name = _T(""), int num = 0, BOOL traceOn = FALSE)
        : m_Name(name), m_Num(num), m_TraceOn(traceOn) {
        trace(Simp::tcerr, _T("User ctor"), m_TraceOn);
    }

    void init(const Simp::tstring& name, int num) {
        m_Name = name;
        m_Num = num;
    }

    // copy ctor
    User(const User& right)
        : m_Name(right.m_Name), m_Num(right.m_Num), m_TraceOn(right.m_TraceOn) {
        trace(Simp::tcerr, _T("User copy ctor"), m_TraceOn);
    }

    // dtor
    ~User() {
        trace(Simp::tcerr, _T("User dtor"), m_TraceOn);
    }

    // assign
    User& operator=(const User& right) {
        trace(Simp::tcerr, _T("User assign"), m_TraceOn);
        if (&right != this) {
            m_Name = right.m_Name;
            m_Num = right.m_Num;
            m_TraceOn = right.m_TraceOn;
        }
        return (*this);
    }

public:

    template <typename CharT>
    std::basic_ostream<CharT>& trace(std::basic_ostream<CharT>& os, const Simp::tstring& msg, BOOL turnOn) const {
        if (turnOn) {
            if (msg != _T(""))
                os << msg << _T(": ");

            _TCHAR buf[32];
            // 字符串最长长度, 支持到 64bit: "obj addr=0x0000000000000000\n"

            _stprintf_s(buf, _countof(buf), _T("0x%0*IX\n"), sizeof(size_t) * 2, this);
            os << buf;
        }
        return os;
    }

    // 输出用户信息到 ostream 流
    template <typename CharT>
    std::basic_ostream<CharT>& Output(std::basic_ostream<CharT>& os) const {
        os << _T("name: ") << m_Name << _T(", number: ") << m_Num;
        return os;
    }

public:

    // 按 num 号码大小, 比较 User 的大小
    BOOL operator<(const User& right) {
        return (m_Num < right.m_Num);
    }

    // 按 num 号码大小, 确定两个 User 是否相同
    BOOL operator==(const User& right) {
        return (m_Num == right.m_Num);
    }

public:
    // getter
    const Simp::tstring& GetName() const {
        return m_Name;
    }
    int GetNum() const {
        return m_Num;
    }

private:
    Simp::tstring   m_Name;      // 名字
    int             m_Num;       // 号码
    BOOL            m_TraceOn;
};

// 输出流操作 os << User
template <typename CharT>
std::basic_ostream<CharT>&
operator<<(std::basic_ostream<CharT>& os, User& user)
{
    return user.Output(os);
}
