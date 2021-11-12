////////////////////////////////////////////////////////////////////////////////
// FILE         : autosp.cpp
// DESCRIPTION  :
//   ��ָ�� deleter �� auto �� SP: class AutoPtr, AutoArr
//   Ĭ�� deleter: StdDel, StdDelArr ���� deleter.cpp
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
// auto ������ָ�� class AutoPtr
////////////////////////////////////////////////////////////////////////////////

// ��ָ�� deleter �� auto ������ָ�� (Transfer ����)

template <class _ClientT, class Del = StdDel<FALSE, FALSE> >
class AutoPtr {
public:
    typedef _ClientT    ClientT;

    explicit AutoPtr(ClientT* ptr = NULL, Del del = Del()) : client_(ptr), del_(del) {}

    // Transfer ����� copy ctor
    AutoPtr(AutoPtr& right) : client_(right.release()) {}

    // ��ת������ (�̳и�) ��� copy ctor
    template <class TR>
    AutoPtr(AutoPtr<TR>& right) : client_(right.release()) {}

    ~AutoPtr() {
        del_(client_);
    }

    // Transfer ����� assign
    AutoPtr& operator=(AutoPtr& right) {
        if (&right != this) {
            del_(client_);
            client_ = right.release();
        }
        return *this;
    }

    // ��ת������ (�̳и�) ��� assign
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

    // ȡ���й�, ����֮ǰ���йܶ���
    ClientT* release() {
        ClientT* p = client_;
        client_ = NULL;
        return p;
    }

    // �����йܶ���
    void reset(ClientT* ptr = NULL) {
        del_(client_);
        client_ = ptr;
    }

private:
    ClientT*    client_;
    Del         del_;
};

////////////////////////////////////////////////////////////////////////////////
// auto ������ָ������� class AutoArr
////////////////////////////////////////////////////////////////////////////////

template <class _ClientT, class Del = StdDelArr<FALSE, FALSE> >
class AutoArr : public AutoPtr<_ClientT, Del> {
public:
    explicit AutoArr(ClientT* ptr = NULL, Del del = Del()) : AutoPtr(ptr, del) {}

    // ������±���йܶ������Ч��, �Ա�֤Ч��
    ClientT& operator[](size_t idx) {
        return get()[idx];
    }
};
