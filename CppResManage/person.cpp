////////////////////////////////////////////////////////////////////////////////
// FILE         : person.cpp
// DESCRIPTION  :
//   RC + COW 简单示例 class Person
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
// class Person 的内部表示 class PersonRep (Representation)
////////////////////////////////////////////////////////////////////////////////

class PersonRep {
    friend class Person;
private:
    PersonRep(int no = 0, const _TCHAR* name = _T("")) : no_(no), name_(name), refCnt_(1) {}
    int         no_;
    tstring     name_;
    UINT        refCnt_;
};

////////////////////////////////////////////////////////////////////////////////
// 人员 class Person
////////////////////////////////////////////////////////////////////////////////

class Person {
public:
    Person(int no = 0, const _TCHAR* name = _T("")) : rep_(new PersonRep(no, name)) {}

    Person(const Person& r) : rep_(r.rep_) {
        ++rep_->refCnt_;
    }

    ~Person() {
        if (--rep_->refCnt_ == 0)
            delete rep_;
    }

    void init(int no, const _TCHAR* name) {
        if (--rep_->refCnt_ == 0)
            delete rep_;
        rep_ = new PersonRep(no, name); // COW
    }

    Person& operator=(const Person& r) {
        if (this == &r || rep_ == r.rep_)
            return *this;

        if (--rep_->refCnt_ == 0)
            delete rep_;
        rep_ = r.rep_;
        ++rep_->refCnt_;
        return *this;
    }

    template <class CharT>
    basic_ostream<CharT>& output(basic_ostream<CharT>& os) const {
        os << _T("[no=") << rep_->no_ << _T(", name=") << rep_->name_ << _T("]");
        return os;
    }

    UINT ref_count() const {
        return rep_->refCnt_;
    }

private:
    PersonRep*  rep_;
};

////////////////////////////////////////////////////////////////////////////////
// class Person 辅助函数
////////////////////////////////////////////////////////////////////////////////

template <class CharT>
basic_ostream<CharT>& operator<<(basic_ostream<CharT>& os, const Person& person)
{
    return person.output(os);
}
