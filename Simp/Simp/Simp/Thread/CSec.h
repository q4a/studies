////////////////////////////////////////////////////////////////////////////////
// 文    件 : CSec.h
// 功能说明 :
//   Windows 的临界区对象
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

SIMP_NS_BEGIN

////////////////////////////////////////////////////////////////////////////////
// Windows 临界区对象类 CriticalSection
////////////////////////////////////////////////////////////////////////////////

class CriticalSection : private Uncopyable {
public:
    CriticalSection() {
        ZeroMemory(&m_CSec, sizeof(m_CSec));
    }

    BOOL Init(DWORD spinCnt = 0) {
        if (!InitializeCriticalSectionAndSpinCount(&m_CSec, spinCnt))
            return FALSE;
        return Lock();
    }

    BOOL Init(DWORD spinCnt, BOOL initOwn = TRUE) {
        if (!InitializeCriticalSectionAndSpinCount(&m_CSec, spinCnt))
            return FALSE;
        if (initOwn)
            return Lock();
        return TRUE;
    }

    ~CriticalSection() {
        Unlock();
        DeleteCriticalSection(&m_CSec);
    }

public:
    // Windows 临界区有自己的保护, 防止自死锁
    // CAUTION: 如果临界区坏掉或检测到死锁, 函数会产生 EXCEPTION_POSSIBLE_DEADLOCK 的 SEH 异常
    BOOL Lock() {
        EnterCriticalSection(&m_CSec);
        return TRUE;
    }

    BOOL Unlock() {
        LeaveCriticalSection(&m_CSec);
        return TRUE;
    }

    BOOL TryLock() {
        return TryEnterCriticalSection(&m_CSec);
    }

    DWORD SetSpinCount(DWORD spin_count) {
        return SetCriticalSectionSpinCount(&m_CSec, spin_count);
    }

private:
    CRITICAL_SECTION m_CSec;
};

SIMP_NS_END
