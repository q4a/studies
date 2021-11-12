// bench_assign.cpp
//
// 对比测试 vector 多元素赋值的 4 种方法的运行效率
// 包括使用使用区间 assign 成员函数
//

////////////////////////////////////////////////////////////////////////////////
// Dependent Libraries
////////////////////////////////////////////////////////////////////////////////

// C Runtime Library (CRT)
#include <sal.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <time.h>
#include <errno.h>
#include <assert.h>

// C++ Standard Library (STL)
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Diagnostic Helpers
////////////////////////////////////////////////////////////////////////////////

#if defined(_DEBUG) || defined(__DEBUG__)
#define dbg_fputs(str, stream)  fputs(str, stream)
#define dbg_getch()             _getch()
#else
#define dbg_fputs(str, stream)  ((void) 0)
#define dbg_getch()             ((void) 0)
#endif

////////////////////////////////////////////////////////////////////////////////
// Test Helpers
////////////////////////////////////////////////////////////////////////////////

#define PRINT_FUNC(fs)  fprintf(fs, "----- %s -----\n", __func__)

////////////////////////////////////////////////////////////////////////////////
// Random Number Helpers
////////////////////////////////////////////////////////////////////////////////

// 产生 [vmin, vmax) 之间的随机整数
errno_t rand_int(_Out_ int& rnd, int vmin, int vmax)
{
    if (vmin > vmax)
        return EINVAL;
    // rand() 的随机度受 RAND_MAX = 32767 (0x7fff) 的限制
    if (vmin > RAND_MAX || vmax > RAND_MAX)
        return ERANGE;

    rnd = (int) ((double) rand() / (RAND_MAX + 1) * (vmax - vmin) + vmin);
    return 0;
}

// 用随机数初始化 vector
void rand_vec_int(_Out_ vector<int>& v, size_t sz, int vmin, int vmax)
{
    v.clear();
    v.resize(sz);
    for (size_t i = 0; i < sz; ++i)
        rand_int(v[i], vmin, vmax);
}

////////////////////////////////////////////////////////////////////////////////
// Container Helpers
////////////////////////////////////////////////////////////////////////////////

template <typename FwdIter>
void print_seq(FwdIter begin, FwdIter end, const char* spec, const char* sep = " ", FILE* fp = stdout)
{
    FwdIter i = begin;
    if (i == end)
        return;
    fprintf(fp, spec, *i);
    for (++i; i != end; ++i) {
        fputs(sep, fp);
        fprintf(fp, spec, *i);
    }
}

// 释放容器的存储
template <typename C>
inline C& clear_alloc(_Inout_ C& c)
{
    C().swap(c);
    return c;
}

////////////////////////////////////////////////////////////////////////////////
// Test Functions
////////////////////////////////////////////////////////////////////////////////

// 以下是 vector 多元素赋值的 4 种方法

// 使用单元素操作 push_back(), 以及显式的循环, 逐个放入元素
// 这种方法的效率最低, 用作与其它方法对比效率的测试基线
template <typename SeqContainer, typename Iter>
inline void seq_assign_baseline(_Out_ SeqContainer& c, Iter begin, Iter end)
{
    c.clear();
    for (Iter i = begin; i != end; ++i)
        c.push_back(*i);
}

// 使用区间 assign 成员函数, 效率最高, 是 Effective STL 中建议使用的方法
template <typename SeqContainer, typename Iter>
inline void seq_assign_range_assgin(_Out_ SeqContainer& c, Iter begin, Iter end)
{
    c.assign(begin, end);
}

// 将 baseline 的单元素操作改写为标准算法 copy
// 这种方法只是将显式的循环移入到 copy 算法的内部, 所以和 baseline 的本质相同
template <typename SeqContainer, typename Iter>
inline void seq_assign_copy_inserter(_Out_ SeqContainer& c, Iter begin, Iter end)
{
    c.clear();
    copy(begin, end, back_inserter(c));
}

// 使用区间 insert 成员函数, 效率较高
template <typename SeqContainer, typename Iter>
inline void seq_assign_range_insert(_Out_ SeqContainer& c, Iter begin, Iter end)
{
    c.clear();
    c.insert(c.end(), begin, end);
}

// 测试序列容器赋值函数 seq_assign 的效率
// 功能是将 v1 的后半部分赋值给 v2
template <typename SeqAssignFunc>
clock_t bench_vecint_assign_rhalf(SeqAssignFunc seq_assign, const vector<int>& v1, _Out_ vector<int>& v2)
{
    clock_t start = clock();
    seq_assign(v2, v1.begin() + v1.size() / 2, v1.end());
    return clock() - start;
}

void bench_range_assign(bool on)
{
    if (!on)
        return;
    PRINT_FUNC(stderr);

    static const size_t     SEQ_SIZE        = 160 * 1024 * 1024 / sizeof(int);  // 160 MB
    static const int        RND_MIN         = -1000;
    static const int        RND_MAX         = 1000;
    static const unsigned   BENCH_ROUND     = 8;

    printf("Generate random vector\n"
           "Size: %Iu (%Iu MB)\n"
           "Random: [%d, %d)\n\n",
           SEQ_SIZE, SEQ_SIZE * sizeof(int) / 1024 / 1024, RND_MIN, RND_MAX);
    printf("Benchmark of vector assign\n"
           "Bench round: %u\n"
           "Elapsed clock (%u clocks/sec):\n"
           "%-15s%-15s%-15s%-15s\n",
           BENCH_ROUND, CLOCKS_PER_SEC, "baseline", "range_assgin", "copy_inserter", "range_insert");

    clock_t deltaSum[4] = {0};
    for (unsigned round = 0; round < BENCH_ROUND; ++round) {
        vector<int> v1;
        rand_vec_int(v1, SEQ_SIZE, RND_MIN, RND_MAX);
        // print_seq(v1.begin(), v1.end(), "%d");

        vector<int> v2_1;
        clock_t delta = bench_vecint_assign_rhalf(seq_assign_baseline<vector<int>, vector<int>::const_iterator>, v1, v2_1);
        printf("%-15ld", delta);
        deltaSum[0] += delta;

        vector<int> v2_2;
        delta = bench_vecint_assign_rhalf(seq_assign_range_assgin<vector<int>, vector<int>::const_iterator>, v1, v2_2);
        printf("%-15ld", delta);
        assert(v2_2 == v2_1);
        deltaSum[1] += delta;

        vector<int> v2_3;
        delta = bench_vecint_assign_rhalf(seq_assign_copy_inserter<vector<int>, vector<int>::const_iterator>, v1, v2_3);
        printf("%-15ld", delta);
        assert(v2_3 == v2_1);
        deltaSum[2] += delta;

        vector<int> v2_4;
        delta = bench_vecint_assign_rhalf(seq_assign_range_insert<vector<int>, vector<int>::const_iterator>, v1, v2_4);
        printf("%-15ld", delta);
        assert(v2_4 == v2_1);
        deltaSum[3] += delta;

        puts("");
    }
    puts("Average:");
    for (unsigned i = 0; i < _countof(deltaSum); ++i)
        printf("%-15ld", deltaSum[i] / BENCH_ROUND);
    puts("");
}

////////////////////////////////////////////////////////////////////////////////
// Entry Point
////////////////////////////////////////////////////////////////////////////////

int main()
{
    setlocale(LC_ALL, "");
    srand((unsigned) time(NULL));

    bench_range_assign(true);

    dbg_fputs("Press any key to Exit...\n", stderr);
    dbg_getch();
    return 0;
}
