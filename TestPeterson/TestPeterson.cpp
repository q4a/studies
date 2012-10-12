////////////////////////////////////////////////////////////////////////////////
// FILE         : TestPeterson.cpp
// DESCRIPTION  :
//   Example of Peterson's algorithm for synchronization in concurrent threads.
//
// AUTHOR       : Breaker Zhao <breaker.zy_AT_gmail>
// DATE         : 2011-10
// LICENSE      : Microsoft Public License <http://www.microsoft.com/en-us/openness/licenses.aspx#MPL>
//
// DISCLAIMER   :
//   THIS CODE IS FOR DEMONSTRATIVE PURPOSES ONLY AND SHOULD NOT BE USED IN THE FINAL PRODUCT.
//   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
//   EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
//   WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
////////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "TestPeterson.h"

////////////////////////////////////////////////////////////////////////////////
// 名字空间
////////////////////////////////////////////////////////////////////////////////

using Simp::LogBaseT;
namespace LOG_LVL = Simp::LOG_LVL;

namespace S = std;
namespace SI = Simp;

using Simp::tcin;
using Simp::tcout;
using Simp::tcerr;

////////////////////////////////////////////////////////////////////////////////
// 全局量
////////////////////////////////////////////////////////////////////////////////

// 原来的工作目录
_TCHAR* OldWorkDir;

// 日志对象
LogBaseT<char>*     LogA;
LogBaseT<wchar_t>*  LogW;
LogBaseT<_TCHAR>*   Log;

////////////////////////////////////////////////////////////////////////////////
// 测试用例
////////////////////////////////////////////////////////////////////////////////

void TestPeterson_01(BOOL turnOn);
void TestAddThreadNoLock(BOOL turnOn);
void TestAddThreadPeterson2(BOOL turnOn);
void TestAddThreadPetersonN(BOOL turnOn);

////////////////////////////////////////////////////////////////////////////////
// 初始化和清理
////////////////////////////////////////////////////////////////////////////////

void Init();
void Uninit();

////////////////////////////////////////////////////////////////////////////////
// 程序入口
////////////////////////////////////////////////////////////////////////////////

int _tmain(int argc, _TCHAR* argv[])
{
    Init();

    TestPeterson_01(TRUE);

    Uninit();
    _putts(_T("Press any key to Exit."));
    _gettch();
    return 0;
}

// 初始化运行环境
void Init()
{
#define _USE_CRT_LOCALE

#if _MSC_VER > 1400
#define _USE_IOS_LOCALE
#endif

// CRT 全局 locale 和 iostream imbue locale 冲突
// VC 2005 问题 (_MSC_VER = 1400)
// VC 2010 正常 (_MSC_VER = 1600)
#if _MSC_VER <= 1400 && defined(_USE_CRT_LOCALE) && defined(_USE_IOS_LOCALE)
#error cannot use CRT global locale and iostream imbue locale at the same time, when _MSC_VER <= 1400
#endif

#ifdef _USE_CRT_LOCALE
    _tsetlocale(LC_ALL, _T(""));
#endif

#ifdef _USE_IOS_LOCALE
    // 设置 C++ iostream 标准 IO 流 locale
    std::locale loc(std::locale(""), std::locale::classic(), std::locale::numeric);
    tcout.imbue(loc);
    tcerr.imbue(loc);
    tcin.imbue(loc);
#endif

    // 设置 CRT 调试输出
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);

    // 设置当前 exe 文件的目录为工作目录
    _TCHAR modDir[BUF_SIZE];
    OldWorkDir = _tgetcwd(NULL, 0);
    Simp::GetModuleDir(GetModuleHandle(NULL), modDir, BUF_SIZE);
    _tchdir(modDir);

    // 设置日志对象
    LogA = Simp::DebugOutLogT<char>(LOG_LVL::LEVEL_DEBUG, BUF_SIZE);
    LogW = Simp::DebugOutLogT<wchar_t>(LOG_LVL::LEVEL_DEBUG, BUF_SIZE);
#ifdef _UNICODE
    Log = LogW;
#else
    Log = LogA;
#endif
}

// 清理运行环境
void Uninit()
{
    // 恢复原来的工作目录
    _tchdir(OldWorkDir);
    free(OldWorkDir);

    // 手工释放日志对象
    LogA->Destroy();
    LogW->Destroy();

    // 因为静态对象在 Uninit 之后析构, 所以需要手工释放含动态存储的静态对象, 否则会有误判
    _CrtDumpMemoryLeaks();
}

////////////////////////////////////////////////////////////////////////////////
// 测试用例
////////////////////////////////////////////////////////////////////////////////

// shared global variable for self-increment (++SharedVal) within multi-threads
int SharedVal;

void TestPeterson_01(BOOL turnOn)
{
    SIMP_OFF_DO(turnOn, return);
    TestAddThreadNoLock(FALSE);
    TestAddThreadPeterson2(FALSE);
    TestAddThreadPetersonN(TRUE);
}

////////////////////////////////////////////////////////////////////////////////
// 非同步方式 (无锁): 将出现 Data Race
////////////////////////////////////////////////////////////////////////////////

DWORD WINAPI AddThreadNoLock(LPVOID param)
{
    int count = (int) (intptr_t) param;
    for (int i = 0; i < count; ++i)
        ++SharedVal;
    return 0;
}

BOOL StartAddThreadNoLock(int threadNum)
{
    const int ADD_NUM_MIN = 10000;
    const int ADD_NUM_MAX = 30000;

    int i = 0;
    int sum = 0;
    SharedVal = 0;

    // 初始化 ThreadPool 中的线程
    S::vector<LPVOID> threadParam(threadNum);
    for (i = 0; i < threadNum; ++i) {
        threadParam[i] = (LPVOID) (intptr_t) (int) (((double) rand() / (double) RAND_MAX) * (ADD_NUM_MAX - ADD_NUM_MIN) + ADD_NUM_MIN);
        sum += (int) (intptr_t) threadParam[i];
    }
    _tprintf(_T("sum: %d\n"), sum);

    SI::ThreadPool threadPool(AddThreadNoLock, &threadParam[0], threadNum);

    // 启动 ThreadPool 中的线程
    if (!threadPool.StartThread())
        MY_RPT(_CRT_ERROR, "ThreadPool::StartThread failed");

    // 等待所有线程结束
    _ASSERTE(threadNum <= MAXIMUM_WAIT_OBJECTS);
    if (threadPool.WaitAllThread(INFINITE) == WAIT_FAILED)
        Log->Log(LOG_LVL::LEVEL_ERROR, FMT("ThreadPool::WaitAllThread failed: %d"), GetLastError());

    _tprintf(_T("shared val: %d\n"), SharedVal);

    return (SharedVal == sum);
}

void TestAddThreadNoLock(BOOL turnOn)
{
    SIMP_OFF_DO(turnOn, return);
    PRINT_FUNC_BEGIN;

    srand((unsigned) time(NULL));

    const int MAX_ROUND = 500;
    int i = 0;
    for (; i < MAX_ROUND; ++i) {
        _tprintf(_T("----- Round %d\n"), i);
        if (!StartAddThreadNoLock(MAXIMUM_WAIT_OBJECTS)) {
            _tprintf(_T("hit singularity!\n"));
            Beep(750, 400);
            break;
        }
    }
    if (i == MAX_ROUND)
        _tprintf(_T("pass all round = %d\n"), i);

    PRINT_FUNC_END;
}

////////////////////////////////////////////////////////////////////////////////
// 使用 Peterson2 同步方法
////////////////////////////////////////////////////////////////////////////////

struct Peterson2 {
    void Init(int id, LPVOID param) {
        m_Id = id;
        m_Param = param;
        m_Turn = 1 - id;
    }

    static void Reset() {
        Flag[0] = FALSE;
        Flag[1] = FALSE;
        Turn = 0;
    }

    template <BOOL UseMemoryBarrier>
    void Lock() {
        Flag[m_Id] = TRUE;
        if (UseMemoryBarrier)
            MemoryBarrier();
        Turn = m_Turn;
        while (Flag[m_Turn] && Turn == m_Turn)  // busy wait
            YieldProcessor();
    }

    void Unlock() {
        Flag[m_Id] = FALSE;
    }

    int     m_Id;
    int     m_Turn;
    LPVOID  m_Param;

    static volatile BOOL    Flag[2];
    static volatile int     Turn;
};

volatile BOOL Peterson2::Flag[2];
volatile int Peterson2::Turn;

template <BOOL UseMemoryBarrier>
DWORD WINAPI AddThreadPeterson2(LPVOID param)
{
    _ASSERTE(param != NULL);
    Peterson2* pet = (Peterson2*) param;
    int count = (int) (intptr_t) pet->m_Param;

    for (int i = 0; i < count; ++i) {
        pet->Lock<UseMemoryBarrier>();
        ++SharedVal;    // Peterson2 critical section
        pet->Unlock();
    }
    return 0;
}

template <BOOL UseMemoryBarrier>
BOOL StartAddThreadPeterson2()
{
    const int ADD_NUM_MIN = 10000;
    const int ADD_NUM_MAX = 30000;

    int i = 0;
    int sum = 0;
    SharedVal = 0;
    Peterson2::Reset(); // IMPORTANT

    // 初始化 ThreadPool 中的线程
    LPVOID threadParam[2];
    Peterson2 pet[2];
    for (i = 0; i < 2; ++i) {
        int cnt = (int) (((double) rand() / (double) RAND_MAX) * (ADD_NUM_MAX - ADD_NUM_MIN) + ADD_NUM_MIN);
        pet[i].Init(i, (LPVOID) (intptr_t) cnt);
        sum += cnt;
        threadParam[i] = &pet[i];
    }
    _tprintf(_T("sum: %d\n"), sum);

    SI::ThreadPool threadPool(AddThreadPeterson2<UseMemoryBarrier>, threadParam, 2);

    // 启动 ThreadPool 中的线程
    if (!threadPool.StartThread())
        MY_RPT(_CRT_ERROR, "ThreadPool::StartThread failed");

    // 等待所有线程结束
    if (threadPool.WaitAllThread(INFINITE) == WAIT_FAILED)
        Log->Log(LOG_LVL::LEVEL_ERROR, FMT("ThreadPool::WaitAllThread failed: %d"), GetLastError());

    _tprintf(_T("shared val: %d\n"), SharedVal);

    return (SharedVal == sum);
}

void TestAddThreadPeterson2(BOOL turnOn)
{
    SIMP_OFF_DO(turnOn, return);
    PRINT_FUNC_BEGIN;

    srand((unsigned) time(NULL));

    const int MAX_ROUND = 500;
    int i = 0;
    for (; i < MAX_ROUND; ++i) {
        _tprintf(_T("----- Round %d\n"), i);
        if (!StartAddThreadPeterson2<TRUE>()) {
            _tprintf(_T("hit singularity!\n"));
            Beep(750, 400);
            break;
        }
    }
    if (i == MAX_ROUND)
        _tprintf(_T("pass all round = %d\n"), i);

    PRINT_FUNC_END;
}

////////////////////////////////////////////////////////////////////////////////
// 使用 PetersonN 同步方法
////////////////////////////////////////////////////////////////////////////////

struct PetersonN {
    void Init(int id, LPVOID param) {
        m_Id = id;
        m_Param = param;
    }

    static void Reset(int threadNum) {
        Clean();
        ThreadNum = threadNum;

        Flag = new int[threadNum + 1];
        ZeroMemory((void*) Flag, (threadNum + 1) * sizeof(int));

        Turn = new int[threadNum];
        ZeroMemory((void*) Turn, threadNum * sizeof(int));
    }

    static void Clean() {
        ThreadNum = 0;
        delete[] Flag;
        Flag = NULL;
        delete[] Turn;
        Turn = NULL;
    }

    template <BOOL UseMemoryBarrier>
    void Lock() {
        for (int i = 1; i <= ThreadNum - 1; ++i) {
            Flag[m_Id] = i;
            if (UseMemoryBarrier)
                MemoryBarrier();
            Turn[i] = m_Id;
            for (int j = 1; j <= ThreadNum; ++j) {
                if (j == m_Id)
                    continue;
                while (Flag[j] >= i && Turn[i] == m_Id)
                    YieldProcessor();
            }
        }
    }

    void Unlock() {
        Flag[m_Id] = 0;
    }

    int     m_Id;
    LPVOID  m_Param;

    static volatile int*    Flag;
    static volatile int*    Turn;
    static int              ThreadNum;
};

volatile int* PetersonN::Flag = NULL;
volatile int* PetersonN::Turn = NULL;
int PetersonN::ThreadNum;

template <BOOL UseMemoryBarrier>
DWORD WINAPI AddThreadPetersonN(LPVOID param)
{
    _ASSERTE(param != NULL);
    PetersonN* pet = (PetersonN*) param;
    int count = (int) (intptr_t) pet->m_Param;

    for (int i = 0; i < count; ++i) {
        pet->Lock<UseMemoryBarrier>();
        ++SharedVal;    // PetersonN critical section
        pet->Unlock();
    }
    return 0;
}

template <BOOL UseMemoryBarrier>
BOOL StartAddThreadPetersonN(int threadNum)
{
    const int ADD_NUM_MIN = 10000;
    const int ADD_NUM_MAX = 30000;

    int i = 0;
    int sum = 0;
    SharedVal = 0;
    PetersonN::Reset(threadNum);

    // 初始化 ThreadPool 中的线程
    S::vector<LPVOID> threadParam(threadNum);
    S::vector<PetersonN> pet(threadNum);
    for (i = 0; i < threadNum; ++i) {
        int cnt = (int) (((double) rand() / (double) RAND_MAX) * (ADD_NUM_MAX - ADD_NUM_MIN) + ADD_NUM_MIN);
        pet[i].Init(i + 1, (LPVOID) (intptr_t) cnt);    // NOTE: first thread id is 1, not 0
        sum += cnt;
        threadParam[i] = &pet[i];
    }
    _tprintf(_T("sum: %d\n"), sum);

    SI::ThreadPool threadPool(AddThreadPetersonN<UseMemoryBarrier>, &threadParam[0], threadNum);

    // 启动 ThreadPool 中的线程
    if (!threadPool.StartThread())
        MY_RPT(_CRT_ERROR, "ThreadPool::StartThread failed");

    // 等待所有线程结束
    _ASSERTE(threadNum <= MAXIMUM_WAIT_OBJECTS);
    if (threadPool.WaitAllThread(INFINITE) == WAIT_FAILED)
        Log->Log(LOG_LVL::LEVEL_ERROR, FMT("ThreadPool::WaitAllThread failed: %d"), GetLastError());

    _tprintf(_T("shared val: %d\n"), SharedVal);

    return (SharedVal == sum);
}

void TestAddThreadPetersonN(BOOL turnOn)
{
    SIMP_OFF_DO(turnOn, return);
    PRINT_FUNC_BEGIN;

    srand((unsigned) time(NULL));

    const int MAX_ROUND = 500;
    const int THREAD_NUM = 4;
    int i = 0;
    for (; i < MAX_ROUND; ++i) {
        _tprintf(_T("----- Round %d\n"), i);
        if (!StartAddThreadPetersonN<FALSE>(THREAD_NUM)) {
            _tprintf(_T("hit singularity!\n"));
            Beep(750, 400);
            break;
        }
    }
    if (i == MAX_ROUND)
        _tprintf(_T("pass all round = %d\n"), i);

    PetersonN::Clean();
    PRINT_FUNC_END;
}
