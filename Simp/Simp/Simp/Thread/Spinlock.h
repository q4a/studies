////////////////////////////////////////////////////////////////////////////////
// 文    件 : Spinlock.h
// 功能说明 :
//   自旋锁
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
// 自旋锁类 SpinLock
////////////////////////////////////////////////////////////////////////////////

class SpinLock : private Uncopyable {
public:
    typedef void (*YieldFunc)();
    typedef long LOCKTYPE;

    enum LOCK_STAT {
        LOCK_UNLOCKED   = 0,    // 必须是 0, 以便 lock 中的 _InterlockedExchange 返回 0
        LOCK_LOCKED     = 1
    };

public:
    // 使用内部 lock_
    SpinLock() : m_Lock(LOCK_UNLOCKED), m_YieldFunc(DefYield) {
        m_LockSlot = &m_Lock;
        Lock();
    }

    // 使用用户提供的 lck
    SpinLock(LOCKTYPE* lock, BOOL initOwn = TRUE, YieldFunc yieldFunc = DefYield) : m_LockSlot(lock), m_YieldFunc(yieldFunc) {
        _ASSERTE(lock != NULL);
        *lock = LOCK_UNLOCKED;
        if (initOwn)
            Lock();
    }

    ~SpinLock() {
        Unlock();
    }

public:
    BOOL Lock() {
        while (_InterlockedExchange(m_LockSlot, LOCK_LOCKED))
            m_YieldFunc();
        return TRUE;
    }

    BOOL Unlock() {
        _InterlockedExchange(m_LockSlot, LOCK_UNLOCKED);
        return TRUE;
    }

private:
    static void DefYield() {
        Sleep(0);
    }

private:
    LOCKTYPE    m_Lock;      // 内部 lock
    LOCKTYPE*   m_LockSlot;
    YieldFunc   m_YieldFunc; // 让出调度函数
};

SIMP_NS_END
