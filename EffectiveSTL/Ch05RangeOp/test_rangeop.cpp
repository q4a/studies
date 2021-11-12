// test_rangeop.cpp
//
// 测试标准容器的区间成员函数 (range member function)
// 区间成员函数 相比于 单元素成员函数 (e.g. insert, push_back, push_front)
// 在操作多元素时, 编写代码更短, 意图更清晰, 运行相率更高
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
#include <fstream>

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

// 用随机数初始化数组
void rand_arr_int(_Out_ int arr[], size_t sz, int vmin, int vmax)
{
    for (size_t i = 0; i < sz; ++i)
        rand_int(arr[i], vmin, vmax);
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

void test_range_construct(bool on)
{
    if (!on)
        return;
    PRINT_FUNC(stderr);

    static const char FNAME_DATA[] = "data.txt";
    ifstream ifs(FNAME_DATA);
    if (!ifs) {
        fprintf(stderr, "Cannot open file: %s\n", FNAME_DATA);
        return;
    }

    // Effective STL Ch6 提到 C/C++ 语法分析倾向于将一堆 () 括号尽可能地解释为函数声明
    // 所以下句不是构造对象, 而是声明了一个名为 v 的函数, 不符合这里的意图
    // vector<int> v(istream_iterator<int>(ifs), istream_iterator<int>());
    // 解决方法: 给函数实参两边加上括号
    vector<int> v((istream_iterator<int>(ifs)), istream_iterator<int>());
    puts("v:");
    print_seq(v.begin(), v.end(), "%d");
    puts("");
}

void test_range_assign(bool on)
{
    if (!on)
        return;
    PRINT_FUNC(stderr);

    static const size_t     SEQ_SIZE        = 32;
    static const int        RND_MIN         = 0;
    static const int        RND_MAX         = 100;

    printf("Generate random vector\n"
           "Size: %Iu (%Iu Bytes)\n"
           "Random: [%d, %d)\n",
           SEQ_SIZE, SEQ_SIZE * sizeof(int), RND_MIN, RND_MAX);

    vector<int> v1, v2;
    rand_vec_int(v1, SEQ_SIZE, RND_MIN, RND_MAX);
    puts("v1:");
    print_seq(v1.begin(), v1.end(), "%d");
    puts("");

    // 将 v1 的后半部分赋值给 v2
    v2.assign(v1.begin() + v1.size() / 2, v1.end());
    puts("v2:");
    print_seq(v2.begin(), v2.end(), "%d");
    puts("");
}

void test_range_insert(bool on)
{
    if (!on)
        return;
    PRINT_FUNC(stderr);

    static const size_t     SEQ_SIZE        = 32;
    static const int        RND_MIN         = 0;
    static const int        RND_MAX         = 100;

    printf("Generate random array\n"
           "Size: %Iu (%Iu Bytes)\n"
           "Random: [%d, %d)\n",
           SEQ_SIZE, SEQ_SIZE * sizeof(int), RND_MIN, RND_MAX);

    vector<int> v2 {1, 2, 3, 4, 5};
    int* a1 = new int[SEQ_SIZE];
    rand_arr_int(a1, SEQ_SIZE, RND_MIN, RND_MAX);
    puts("a1:");
    print_seq(a1, a1 + SEQ_SIZE, "%d");
    puts("");

    // 将数组 a1 插入到 v2 的前面
    v2.insert(v2.begin(), a1, a1 + SEQ_SIZE);
    puts("v2:");
    print_seq(v2.begin(), v2.end(), "%d");
    puts("");
}

////////////////////////////////////////////////////////////////////////////////
// Entry Point
////////////////////////////////////////////////////////////////////////////////

int main()
{
    setlocale(LC_ALL, "");
    srand((unsigned) time(NULL));

    test_range_assign(false);
    test_range_insert(false);
    test_range_construct(true);

    dbg_fputs("Press any key to Exit...\n", stderr);
    dbg_getch();
    return 0;
}
