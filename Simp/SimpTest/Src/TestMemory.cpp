// TestMemory.cpp
//

#include "StdAfx.h"
#include "SimpTest.h"
#include "TestMemory.h"

#include "Common/User.h"

////////////////////////////////////////////////////////////////////////////////
// √˚◊÷ø’º‰
////////////////////////////////////////////////////////////////////////////////

using std::endl;

using Simp::tstring;
using Simp::tcin;
using Simp::tcout;
using Simp::tcerr;
using Simp::ToTchar;

using Simp::Mallocator;
using Simp::AutoPtr;
using Simp::AutoArr;
using Simp::ScopedBuf;

////////////////////////////////////////////////////////////////////////////////
// ≤‚ ‘”√¿˝
////////////////////////////////////////////////////////////////////////////////

void TestDeleter(BOOL turnOn);
void TestAlloc(BOOL turnOn);
void TestAutoPtr(BOOL turnOn);
void TestAutoBuf(BOOL turnOn);

////////////////////////////////////////////////////////////////////////////////
// ≤‚ ‘∫Ø ˝
////////////////////////////////////////////////////////////////////////////////

void TestMemory(BOOL turnOn)
{
    SIMP_OFF_DO(turnOn, return);

    TestDeleter(TRUE);
    TestAlloc(FALSE);
    TestAutoPtr(FALSE);
    TestAutoBuf(TRUE);
}

void TestAlloc(BOOL turnOn)
{
    SIMP_OFF_DO(turnOn, return);
    PRINT_FUNC_BEGIN;

    Mallocator<User> ac;
    Mallocator<User>::Type* p = ac.Alloc(100);
    ac.Construct(p, User(_T("Zhang San"), 42));
    tcout << _T("user: ") << *p << endl;
    ac.Destroy(p);
    ac.Free(p);

    PRINT_FUNC_END;
}

void TestAutoPtr(BOOL turnOn)
{
    SIMP_OFF_DO(turnOn, return);
    PRINT_FUNC_BEGIN;

    AutoPtr<User> user(new User(_T("Zhang San"), 42));
    tcout << _T("AutoPtr size: ") << sizeof(user) << endl;

    AutoArr<char> buf(new char[100]);
    Simp::ZeroArray(buf.Get(), 100);
    buf[4] = 'c';
    // buf.release();   // ≤‚ ‘ƒ⁄¥Ê–π¬©

#pragma warning(push)
#pragma warning(disable: 4996)
    AutoPtr<FILE, Simp::FClose<TRUE, TRUE> > file(_tfopen(_T("xxx.txt"), _T("r")));
#pragma warning(pop)

    FILE* fp = file.Get();

    PRINT_FUNC_END;
}

void TestAutoBuf(BOOL turnOn)
{
    SIMP_OFF_DO(turnOn, return);
    PRINT_FUNC_BEGIN;

    ScopedBuf<char> buf(100, 0);
    buf.Expand();
    tcout << _T("buf size: ") << buf.Size() << endl;
    buf[4] = 'c';
    // buf.detach();   // ≤‚ ‘ƒ⁄¥Ê–π¬©

    PRINT_FUNC_END;
}

void TestDeleter(BOOL turnOn)
{
    SIMP_OFF_DO(turnOn, return);
    PRINT_FUNC_BEGIN;

    using Simp::STDDEL_CZ;
    using Simp::STDDELARR_CZ;

    User* p1 = new User(_T("Zhang San"), 42);
    tcout << *p1 << endl;

    Delete(p1, STDDEL_CZ);

    User* p2 = new User[3];
    p2[0].init(_T("Li Si"), 42);
    p2[1].init(_T("Wang Wu"), 43);
    p2[2].init(_T("Liu Ke"), 44);
    tcout << p2[0] << _T("\n")
          << p2[1] << _T("\n")
          << p2[2] << endl;

    Delete(p2, STDDELARR_CZ);

    PRINT_FUNC_END;
}
