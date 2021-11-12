////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��  ��: TestPeterson.cpp
// ˵  ��:
//   ���Բ����߳� Peterson ͬ���㷨
//
// ��  ��: 1.0
// ��  ��: Breaker Zhao <breakerzhao@qq.com>
// ��  ��: 2011.10
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "TestPeterson.h"
#include "ThreadPool.h"
#include "Spinlock.h"

// ��Ҫʹ�� Unicode �ַ������ܱ���
#if !defined(_UNICODE) || !defined(UNICODE)
#error Must be built with Unicode Character Set
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using std::vector;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// �ۼ��̲߳��Ի��� TestThreadAccBaseline ʹ�õ�ͬ����ʽ
enum SYNC_MODE
{
    SYNC_MODEMIN            = 0,
    SYNC_NOLOCK             = 0,    // û��ʹ����, ��Ȼ����� Data Race
    SYNC_CRITICALSECTION    = 1,    // ʹ���ٽ�������
    SYNC_ATOMIC             = 2,    // ʹ��ԭ�Ӳ���
    SYNC_SPINLOCK           = 3,    // ʹ��������
    SYNC_MODEMAX            = 3
};

const wchar_t* SYNC_MODE_NAME[] = {
    L"SYNC_NOLOCK",
    L"SYNC_CRITICALSECTION",
    L"SYNC_ATOMIC",
    L"SYNC_SPINLOCK"
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ȫ�ֱ���
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const wchar_t       PROGRAM_NAME[]      = L"TestPeterson";

// ÿ���̵߳��ۼ�ֵ��������
// Ԥ���ۼ�ֵ (Expected AccVal) = �����̵߳��ۼ�ֵ֮��
const int           ACC_MIN             = 10000;
const int           ACC_MAX             = 30000;

// �����Իغ�
const unsigned      MAX_TEST_ROUND      = 500;

// �����߳�����, ���� ���� 1. (Baseline) �� ���� 3. (PetersonN)
// ���� 2. (Peterson2) �е��߳������̶�Ϊ 2
// THREAD_COUNT �����ֵΪ MAXIMUM_WAIT_OBJECTS (64), �����̳߳��� ThreadPool ֧�ֵ�����߳���
const int           THREAD_COUNT        = 4;

// ���߳̽����ۼӲ����Ĺ���ȫ�ֱ���
int                 g_AccVal;

// ���ڱ�֤�����̵߳��ۼӲ������� (Mutual-Exclusion) ���ٽ�������
CRITICAL_SECTION    g_CSecAcc;

// ������� g_CSecAcc ����������
// ���λ��λ (High-order Bit) ��Ϊ�˼��� Win2000 ��Ԥ�����ٽ��������ڲ��� Event ����
// WinXP ֮��� Event ������ð������ (Allocated on Demand), ���λ��λ�ᱻ����
const DWORD         CSEC_SPINCOUNT  = 0x80000400;   // �������� 400 (Hex) = 1024

// ���� Spinlock ����� SpinSlot
volatile long       g_SpinSlot;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ������������
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <int SyncMode>
void TestThreadAccBaseline(bool on);

template <bool UseMemoryBarrier>
void TestThreadAccPeterson2(bool on);

template <bool UseMemoryBarrier>
void TestThreadAccPetersonN(bool on);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����������������
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LaunchTest();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��ʼ��������������
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Setup();
void Exit(int err);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ������ں���
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
// ��ʼ����������
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Setup()
{
    // ʹ���û�Ĭ�� locale
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
// ������������
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LaunchTest()
{
    TestThreadAccBaseline<SYNC_SPINLOCK>(false);
    TestThreadAccPeterson2<true>(false);
    TestThreadAccPetersonN<true>(true);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��Ϊ���Ի��ߵ��ۼ��߳�
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

    // ��ʼ�� ThreadPool �е��߳�
    vector<LPVOID> threadParam(threadCnt);
    for (int i = 0; i < threadCnt; ++i) {
        threadParam[i] = (LPVOID) (intptr_t) (int) (((double) rand() / RAND_MAX) * (ACC_MAX - ACC_MIN) + ACC_MIN);
        exp += (int) (intptr_t) threadParam[i];
    }
    wprintf(L"Expected AccVal: %d\n", exp);

    ThreadPool threadPool(ThreadAccBaseline<SyncMode>, &threadParam[0], threadCnt);

    if (SyncMode == SYNC_CRITICALSECTION) {
        // ��ʼ���ٽ�������
        if (!InitializeCriticalSectionAndSpinCount(&g_CSecAcc, CSEC_SPINCOUNT)) {
            fwprintf(stderr, L"InitializeCriticalSectionAndSpinCount failed: %d\n", GetLastError());
            Exit(-1);
        }
    }
    else if (SyncMode == SYNC_SPINLOCK) {
        Spinlock::InitSpinSlot(&g_SpinSlot);
    }

    // ���� ThreadPool �е��߳�
    if (!threadPool.StartThreads()) {
        fwprintf(stderr, L"ThreadPool::StartThread failed\n");
        Exit(-1);
    }

    // �ȴ������߳̽���
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
// ʹ�� Peterson2 ͬ���㷨���ۼ��߳�
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

    // ��ʼ�� ThreadPool �е��߳�
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

    // ���� ThreadPool �е��߳�
    if (!threadPool.StartThreads()) {
        fwprintf(stderr, L"ThreadPool::StartThread failed\n");
        Exit(-1);
    }

    // �ȴ������߳̽���
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
// ʹ�� PetersonN ͬ���㷨���ۼ��߳�
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

    // ��ʼ�� ThreadPool �е��߳�
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

    // ���� ThreadPool �е��߳�
    if (!threadPool.StartThreads()) {
        fwprintf(stderr, L"ThreadPool::StartThread failed\n");
        Exit(-1);
    }

    // �ȴ������߳̽���
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
