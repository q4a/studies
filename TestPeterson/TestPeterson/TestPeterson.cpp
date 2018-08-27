////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 文  件: TestPeterson.cpp
// 说  明:
//   测试并发线程 Peterson 同步算法
//
// 版  本: 1.0
// 作  者: Breaker Zhao <breakerzhao@qq.com>
// 日  期: 2011.10
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "TestPeterson.h"
#include "ThreadPool.h"
#include "Spinlock.h"

// 需要使用 Unicode 字符集才能编译
#if !defined(_UNICODE) || !defined(UNICODE)
#error Must be built with Unicode Character Set
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 名字声明
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using std::vector;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 类型声明
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 累加线程测试基线 TestThreadAccBaseline 使用的同步方式
enum SYNC_MODE
{
    SYNC_MODEMIN            = 0,
    SYNC_NOLOCK             = 0,    // 没有使用锁, 必然会出现 Data Race
    SYNC_CRITICALSECTION    = 1,    // 使用临界区对象
    SYNC_ATOMIC             = 2,    // 使用原子操作
    SYNC_SPINLOCK           = 3,    // 使用自旋锁
    SYNC_MODEMAX            = 3
};

const wchar_t* SYNC_MODE_NAME[] = {
    L"SYNC_NOLOCK",
    L"SYNC_CRITICALSECTION",
    L"SYNC_ATOMIC",
    L"SYNC_SPINLOCK"
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 全局变量
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const wchar_t       PROGRAM_NAME[]      = L"TestPeterson";

// 每个线程的累加值的上下限
// 预期累加值 (Expected AccVal) = 所有线程的累加值之和
const int           ACC_MIN             = 10000;
const int           ACC_MAX             = 30000;

// 最大测试回合
const unsigned      MAX_TEST_ROUND      = 500;

// 测试线程数量, 用于 用例 1. (Baseline) 和 用例 3. (PetersonN)
// 用例 2. (Peterson2) 中的线程数量固定为 2
// THREAD_COUNT 的最大值为 MAXIMUM_WAIT_OBJECTS (64), 这是线程池类 ThreadPool 支持的最大线程数
const int           THREAD_COUNT        = 4;

// 多线程进行累加操作的共享全局变量
int                 g_AccVal;

// 用于保证并发线程的累加操作互斥 (Mutual-Exclusion) 的临界区对象
CRITICAL_SECTION    g_CSecAcc;

// 用于配合 g_CSecAcc 的自旋计数
// 最高位置位 (High-order Bit) 是为了兼容 Win2000 的预分配临界区对象内部的 Event 对象
// WinXP 之后此 Event 对象采用按需分配 (Allocated on Demand), 最高位置位会被忽略
const DWORD         CSEC_SPINCOUNT  = 0x80000400;   // 自旋计数 400 (Hex) = 1024

// 用于 Spinlock 对象的 SpinSlot
volatile long       g_SpinSlot;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 测试用例声明
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <int SyncMode>
void TestThreadAccBaseline(bool on);

template <bool UseMemoryBarrier>
void TestThreadAccPeterson2(bool on);

template <bool UseMemoryBarrier>
void TestThreadAccPetersonN(bool on);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 测试启动函数声明
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LaunchTest();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 初始化和清理函数声明
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Setup();
void Exit(int err);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 程序入口函数
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int wmain(int argc, wchar_t* argv[])
{
    if (!Setup()) {
        fwprintf(stderr, L"%s setup failed.\n", PROGRAM_NAME);
        return -1;
    }

    LaunchTest();
    Exit(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 初始化和清理函数
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Setup()
{
    // 使用用户默认 locale
    _wsetlocale(LC_ALL, L"");
    srand((unsigned) time(NULL));
    return true;
}

void Exit(int err)
{
#if defined(_EXIT_PROMPT) || defined(_DEBUG)
    _putws(L"Press any key to Exit...");
    _getwch();
#endif
    exit(err);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 测试启动函数
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LaunchTest()
{
    TestThreadAccBaseline<SYNC_SPINLOCK>(false);
    TestThreadAccPeterson2<true>(false);
    TestThreadAccPetersonN<true>(true);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 测试用例
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 作为测试基线的累加线程
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <int SyncMode>
DWORD WINAPI ThreadAccBaseline(LPVOID param)
{
    int count = (int) (intptr_t) param;
    Spinlock lock(&g_SpinSlot, false);

    for (int i = 0; i < count; ++i) {
        if (SyncMode == SYNC_NOLOCK) {
            ++g_AccVal;
        }
        else if (SyncMode == SYNC_CRITICALSECTION) {
            EnterCriticalSection(&g_CSecAcc);
            ++g_AccVal;
            LeaveCriticalSection(&g_CSecAcc);
        }
        else if (SyncMode == SYNC_ATOMIC) {
            _InterlockedIncrement((long*) &g_AccVal);
        }
        else if (SyncMode == SYNC_SPINLOCK) {
            lock.Lock();
            ++g_AccVal;
            lock.Unlock();
        }
    }
    return 0;
}

template <int SyncMode>
bool StartThreadAccBaseline(int threadCnt)
{
    int exp     = 0;
    g_AccVal    = 0;

    // 初始化 ThreadPool 中的线程
    vector<LPVOID> threadParam(threadCnt);
    for (int i = 0; i < threadCnt; ++i) {
        threadParam[i] = (LPVOID) (intptr_t) (int) (((double) rand() / RAND_MAX) * (ACC_MAX - ACC_MIN) + ACC_MIN);
        exp += (int) (intptr_t) threadParam[i];
    }
    wprintf(L"Expected AccVal: %d\n", exp);

    ThreadPool threadPool(ThreadAccBaseline<SyncMode>, &threadParam[0], threadCnt);

    if (SyncMode == SYNC_CRITICALSECTION) {
        // 初始化临界区对象
        if (!InitializeCriticalSectionAndSpinCount(&g_CSecAcc, CSEC_SPINCOUNT)) {
            fwprintf(stderr, L"InitializeCriticalSectionAndSpinCount failed: %d\n", GetLastError());
            Exit(-1);
        }
    }
    else if (SyncMode == SYNC_SPINLOCK) {
        Spinlock::InitSpinSlot(&g_SpinSlot);
    }

    // 启动 ThreadPool 中的线程
    if (!threadPool.StartThreads()) {
        fwprintf(stderr, L"ThreadPool::StartThread failed\n");
        Exit(-1);
    }

    // 等待所有线程结束
    _ASSERTE(threadCnt <= MAXIMUM_WAIT_OBJECTS);
    if (threadPool.WaitThreads(INFINITE) == WAIT_FAILED) {
        fwprintf(stderr, L"ThreadPool::WaitAllThread failed: %d\n", GetLastError());
        Exit(-1);
    }

    if (SyncMode == SYNC_CRITICALSECTION)
        DeleteCriticalSection(&g_CSecAcc);

    wprintf(L"Shared AccVal: %d\n", g_AccVal);
    return (g_AccVal == exp);
}

template <int SyncMode>
void TestThreadAccBaseline(bool on)
{
    if (!on)
        return;
    PRINT_FUNC(stderr);

    _ASSERTE(SyncMode >= SYNC_MODEMIN && SyncMode <= SYNC_MODEMAX);
    wprintf(L"SyncMode: %s\n"
            L"Thread Count: %u\n"
            L"Test Round: %u\n\n",
            SYNC_MODE_NAME[SyncMode], THREAD_COUNT, MAX_TEST_ROUND);

    for (unsigned i = 0; i < MAX_TEST_ROUND; ++i) {
        wprintf(L"Round %u\n", i);
        if (!StartThreadAccBaseline<SyncMode>(THREAD_COUNT)) {
            wprintf(L"Hit Data Race!\n");
            Beep(750, 500);
            return;
        }
    }
    wprintf(L"Pass All Round (%u)\n", MAX_TEST_ROUND);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 使用 Peterson2 同步算法的累加线程
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Peterson2
{
    void Init(int id, LPVOID param)
    {
        m_Id = id;
        m_Param = param;
        m_Turn = 1 - id;
    }

    static void Reset()
    {
        Flag[0] = false;
        Flag[1] = false;
        Turn = 0;
    }

    template <bool UseMemoryBarrier>
    void Lock()
    {
        Flag[m_Id] = true;
        if (UseMemoryBarrier)
            MemoryBarrier();
        Turn = m_Turn;
        while (Flag[m_Turn] && Turn == m_Turn)  // Busy wait
            YieldProcessor();
    }

    void Unlock()
    {
        Flag[m_Id] = false;
    }

    int     m_Id;
    int     m_Turn;
    LPVOID  m_Param;

    static volatile bool    Flag[2];
    static volatile int     Turn;
};

volatile bool Peterson2::Flag[2];
volatile int Peterson2::Turn;

template <bool UseMemoryBarrier>
DWORD WINAPI ThreadAccPeterson2(LPVOID param)
{
    _ASSERTE(param != NULL);
    Peterson2* pet = (Peterson2*) param;
    int count = (int) (intptr_t) pet->m_Param;

    for (int i = 0; i < count; ++i) {
        pet->Lock<UseMemoryBarrier>();
        ++g_AccVal;
        pet->Unlock();
    }
    return 0;
}

template <bool UseMemoryBarrier>
bool StartThreadAccPeterson2()
{
    int exp     = 0;
    g_AccVal    = 0;
    Peterson2::Reset();

    // 初始化 ThreadPool 中的线程
    LPVOID threadParam[2];
    Peterson2 pet[2];
    for (int i = 0; i < 2; ++i) {
        int cnt = (int) (((double) rand() / RAND_MAX) * (ACC_MAX - ACC_MIN) + ACC_MIN);
        pet[i].Init(i, (LPVOID) (intptr_t) cnt);
        exp += cnt;
        threadParam[i] = &pet[i];
    }
    wprintf(L"Expected AccVal: %d\n", exp);

    ThreadPool threadPool(ThreadAccPeterson2<UseMemoryBarrier>, threadParam, 2);

    // 启动 ThreadPool 中的线程
    if (!threadPool.StartThreads()) {
        fwprintf(stderr, L"ThreadPool::StartThread failed\n");
        Exit(-1);
    }

    // 等待所有线程结束
    if (threadPool.WaitThreads(INFINITE) == WAIT_FAILED) {
        fwprintf(stderr, L"ThreadPool::WaitAllThread failed: %d\n", GetLastError());
        Exit(-1);
    }

    wprintf(L"Shared AccVal: %d\n", g_AccVal);
    return (g_AccVal == exp);
}

template <bool UseMemoryBarrier>
void TestThreadAccPeterson2(bool on)
{
    if (!on)
        return;
    PRINT_FUNC(stderr);

    wprintf(L"UseMemoryBarrier: %s\n"
            L"Thread Count: 2\n"
            L"Test Round: %u\n\n",
            (UseMemoryBarrier ? L"on" : L"off"), MAX_TEST_ROUND);

    for (unsigned i = 0; i < MAX_TEST_ROUND; ++i) {
        wprintf(L"Round %u\n", i);
        if (!StartThreadAccPeterson2<UseMemoryBarrier>()) {
            wprintf(L"Hit Data Race!\n");
            Beep(750, 500);
            return;
        }
    }
    wprintf(L"Pass All Round (%u)\n", MAX_TEST_ROUND);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 使用 PetersonN 同步算法的累加线程
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct PetersonN
{
    void Init(int id, LPVOID param)
    {
        m_Id = id;
        m_Param = param;
    }

    static void Reset(int threadCnt)
    {
        Clean();
        ThreadNum = threadCnt;

        Flag = new int[threadCnt + 1];
        ZeroMemory((void*) Flag, (threadCnt + 1) * sizeof(int));

        Turn = new int[threadCnt];
        ZeroMemory((void*) Turn, threadCnt * sizeof(int));
    }

    static void Clean()
    {
        ThreadNum = 0;
        delete[] Flag;
        Flag = NULL;
        delete[] Turn;
        Turn = NULL;
    }

    template <bool UseMemoryBarrier>
    void Lock()
    {
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

    void Unlock()
    {
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

template <bool UseMemoryBarrier>
DWORD WINAPI ThreadAccPetersonN(LPVOID param)
{
    _ASSERTE(param != NULL);
    PetersonN* pet = (PetersonN*) param;
    int count = (int) (intptr_t) pet->m_Param;

    for (int i = 0; i < count; ++i) {
        pet->Lock<UseMemoryBarrier>();
        ++g_AccVal;
        pet->Unlock();
    }
    return 0;
}

template <bool UseMemoryBarrier>
bool StartThreadAccPetersonN(int threadCnt)
{
    int exp     = 0;
    g_AccVal    = 0;
    PetersonN::Reset(threadCnt);

    // 初始化 ThreadPool 中的线程
    vector<LPVOID> threadParam(threadCnt);
    vector<PetersonN> pet(threadCnt);
    for (int i = 0; i < threadCnt; ++i) {
        int cnt = (int) (((double) rand() / RAND_MAX) * (ACC_MAX - ACC_MIN) + ACC_MIN);
        pet[i].Init(i + 1, (LPVOID) (intptr_t) cnt);    // NOTE: First thread ID is 1, Not 0
        exp += cnt;
        threadParam[i] = &pet[i];
    }
    wprintf(L"Expected AccVal: %d\n", exp);

    ThreadPool threadPool(ThreadAccPetersonN<UseMemoryBarrier>, &threadParam[0], threadCnt);

    // 启动 ThreadPool 中的线程
    if (!threadPool.StartThreads()) {
        fwprintf(stderr, L"ThreadPool::StartThread failed\n");
        Exit(-1);
    }

    // 等待所有线程结束
    _ASSERTE(threadCnt <= MAXIMUM_WAIT_OBJECTS);
    if (threadPool.WaitThreads(INFINITE) == WAIT_FAILED) {
        fwprintf(stderr, L"ThreadPool::WaitAllThread failed: %d\n", GetLastError());
        Exit(-1);
    }

    wprintf(L"Shared AccVal: %d\n", g_AccVal);
    return (g_AccVal == exp);
}

template <bool UseMemoryBarrier>
void TestThreadAccPetersonN(bool on)
{
    if (!on)
        return;
    PRINT_FUNC(stderr);

    wprintf(L"UseMemoryBarrier: %s\n"
            L"Thread Count: %u\n"
            L"Test Round: %u\n\n",
            (UseMemoryBarrier ? L"on" : L"off"), THREAD_COUNT, MAX_TEST_ROUND);

    for (unsigned i = 0; i < MAX_TEST_ROUND; ++i) {
        wprintf(L"Round %u\n", i);
        if (!StartThreadAccPetersonN<UseMemoryBarrier>(THREAD_COUNT)) {
            wprintf(L"Hit Data Race!\n");
            Beep(750, 500);
            return;
        }
    }
    wprintf(L"Pass All Round (%u)\n", MAX_TEST_ROUND);
    PetersonN::Clean();
}
