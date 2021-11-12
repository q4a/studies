////////////////////////////////////////////////////////////////////////////////
// FILE         : autosp.cpp
// DESCRIPTION  :
//   可指定 deleter 的 auto 型 SP: class AutoPtr, AutoArr
//   默认 deleter: StdDel, StdDelArr 来自 deleter.cpp
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
// auto 型智能指针 class AutoPtr
////////////////////////////////////////////////////////////////////////////////

// 可指定 deleter 的 auto 型智能指针 (Transfer 语义)

template <class _ClientT, class Del = StdDel<FALSE, FALSE> >
class AutoPtr {
public:
    typedef _ClientT    ClientT;

    explicit AutoPtr(ClientT* ptr = NULL, Del del = Del()) : client_(ptr), del_(del) {}

    // Transfer 语义的 copy ctor
    AutoPtr(AutoPtr& right) : client_(right.release()) {}

    // 可转换类型 (继承格) 间的 copy ctor
    template <class TR>
    AutoPtr(AutoPtr<TR>& right) : client_(right.release()) {}

    ~AutoPtr() {
        del_(client_);
    }

    // Transfer 语义的 assign
    AutoPtr& operator=(AutoPtr& right) {
        if (&right != this) {
            del_(client_);
            client_ = right.release();
        }
        return *this;
    }

    // 可转换类型 (继承格) 间的 assign
    template <class TR>
    AutoPtr& operator=(AutoPtr<TR>& right) {
        if (right.get() != client_) {
            del_(client_);
            client_ = right.release();
        }
        return *this;
    }

    ClientT* get() const {
        return client_;
    }

    ClientT* operator->() const {
        return client_;
    }

    ClientT& operator*() const {
        return *client_;
    }

    // 取消托管, 返回之前的托管对象
    ClientT* release() {
        ClientT* p = client_;
        client_ = NULL;
        return p;
    }

    // 重置托管对象
    void reset(ClientT* ptr = NULL) {
        del_(client_);
        client_ = ptr;
    }

private:
    ClientT*    client_;
    Del         del_;
};

////////////////////////////////////////////////////////////////////////////////
// auto 型智能指针数组版 class AutoArr
////////////////////////////////////////////////////////////////////////////////

template <class _ClientT, class Del = StdDelArr<FALSE, FALSE> >
class AutoArr : public AutoPtr<_ClientT, Del> {
public:
    explicit AutoArr(ClientT* ptr = NULL, Del del = Del()) : AutoPtr(ptr, del) {}

    // 不检查下标和托管对象的有效性, 以保证效率
    ClientT& operator[](size_t idx) {
        return get()[idx];
    }
};
