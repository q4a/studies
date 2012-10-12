////////////////////////////////////////////////////////////////////////////////
// 文    件 : Mutex.h
// 功能说明 :
//   Windows 的互斥体
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
// Windows 互斥体类 Mutex
////////////////////////////////////////////////////////////////////////////////

class Mutex : private Uncopyable {
public:
    Mutex() : m_Mutex(NULL) {}

    // 初始化错误码
    enum INIT_STAT {
        INIT_SUCCESS    = 0,
        INIT_EXISTED    = 1,
        INIT_FAILED     = -1
    };

    INIT_STAT Init() {
        m_Mutex = CreateMutex(NULL, TRUE, NULL);
        if (m_Mutex == NULL)
            return INIT_FAILED;
        return INIT_SUCCESS;
    }

    INIT_STAT Init(const _TCHAR* mutexName, BOOL initOwn = TRUE, LPSECURITY_ATTRIBUTES secAttr = NULL) {
        m_Mutex = CreateMutex(secAttr, initOwn, mutexName);
        if (m_Mutex == NULL)
            return INIT_FAILED;
        if (GetLastError() == ERROR_ALREADY_EXISTS)
            return INIT_EXISTED;
        return INIT_SUCCESS;
    }

    ~Mutex() {
        Unlock();
        CloseHandle(m_Mutex);
    }

public:
    // Lock 操作错误码
    enum LOCK_STAT {
        LOCK_SUCCESS    = WAIT_OBJECT_0,
        LOCK_ABANDONED  = WAIT_ABANDONED,
        LOCK_TIMEOUT    = WAIT_TIMEOUT
    };

    // timeout 以 millisec 为单位, Windows 互斥体有自己的保护防止自死锁
    LOCK_STAT Lock(DWORD timeout) {
        return (LOCK_STAT) WaitForSingleObject(m_Mutex, timeout);
    }

    BOOL Lock() {
        return (Lock(INFINITE) == LOCK_SUCCESS);
    }

    BOOL Unlock() {
        return ReleaseMutex(m_Mutex);
    }

private:
    HANDLE m_Mutex;
};

SIMP_NS_END
