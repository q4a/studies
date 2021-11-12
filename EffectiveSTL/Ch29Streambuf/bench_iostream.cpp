// bench_iostream.cpp
//
// 测试将字符串输出到文件流时 (包括 stdout)
// 采用以下几种方式的运行效率:
// 1. stdio puts
// 2. stdio printf
// 3. iostream
// 4. streambuf
//
// 已测试工具链 MSVC 9.0, MinGW GCC 8.1.0
// 源文件编码: UTF-8 + BOM
//

////////////////////////////////////////////////////////////////////////////////
// Dependent Libraries
////////////////////////////////////////////////////////////////////////////////

// C Runtime Library (CRT)
#define _CRT_RAND_S     1   // Using security-enhanced rand_s()

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <locale.h>
#include <conio.h>
#include <time.h>
#include <wchar.h>
#include <sal.h>
#include <errno.h>
#include <string.h>

// C++ Standard Library (STL)
#include <ios>
#include <string>
#include <iostream>
#include <streambuf>
#include <locale>
#include <iterator>
#include <algorithm>
#include <vector>

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
// Type Definitions
////////////////////////////////////////////////////////////////////////////////

typedef std::vector<std::wstring>   WstrVec;

////////////////////////////////////////////////////////////////////////////////
// Globals
////////////////////////////////////////////////////////////////////////////////

const char      PROGRAM_NAME[]  = "bench_iostream";
const wchar_t   MSG_GREETING[]  = L"Hello World! 你好，世界！";

////////////////////////////////////////////////////////////////////////////////
// Random Number Helpers
////////////////////////////////////////////////////////////////////////////////

// Generates a random integer in range [vmin, vmax)
errno_t rand_int(_Out_ int& rnd, int vmin, int vmax)
{
    if (vmin > vmax)
        return EINVAL;

#ifdef _CRT_RAND_S
    // rand_s() generates a cryptographically secure pseudorandom unsigned int in range [0, UINT_MAX]
    // rand_s() depends on RtlGenRandom(), and does not use srand() seed.
    unsigned rnd0;
    errno_t err = rand_s(&rnd0);
    if (err)
        return err;
    rnd = (int) ((double) rnd0 / UINT_MAX * (vmax - vmin) + vmin);
#else
// _CRT_RAND_S undefined
    if (vmax > RAND_MAX)
        return ERANGE;
    // rand() generates a pseudorandom int in range [0, RAND_MAX), RAND_MAX = 32767 (0x7fff)
    // Use srand() to seed rand().
    rnd = (int) ((double) rand() / (RAND_MAX + 1) * (vmax - vmin) + vmin);
#endif
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
// Test Functions
////////////////////////////////////////////////////////////////////////////////

void test_streambuf(bool on)
{
    if (!on)
        return;

    wstreambuf* osb = wcout.rdbuf();
    osb->sputn(MSG_GREETING, _countof(MSG_GREETING));
    endl(wcout);
}

void test_streambuf_iterator(bool on)
{
    if (!on)
        return;

    ostreambuf_iterator<wchar_t> osi(wcout);
    copy(MSG_GREETING, MSG_GREETING + _countof(MSG_GREETING), osi);
    endl(wcout);
}

// [某次测试示例]
//
// 测试参数:
// bench_iostream.exe -n:1000 -l:1000 >NUL
//
// MinGW GCC 8.1.0 x64 Release 配置测试结果:
// stdio puts elapsed: 0.054000
// stdio printf elapsed: 0.062000
// iostream elapsed: 0.054000
// streambuf elapsed: 0.041000
//
// MSVC 9.0 x64 Release 配置测试结果:
// stdio puts elapsed: 0.072000
// stdio printf elapsed: 0.065000
// iostream elapsed: 2.285000
// streambuf elapsed: 2.443000
//
// 结论:
// MSVCRT 的 iostream 和 streambuf 太慢
void bench_iostream(bool on, unsigned numstr, unsigned lenstr)
{
    if (!on)
        return;

    // 产生 numstr 个长度为 lenstr 的随机字符串
    unsigned i, j;
    int ch = 0;
    WstrVec strs(numstr);
    for (i = 0; i < numstr; ++i) {
        wstring& str = strs[i];
        str.resize(lenstr);
        for (j = 0; j < lenstr; ++j) {
            rand_int(ch, ' ', '~');
            str[j] = ch;
        }
    }

    // Benchmark:

    clock_t start, stop;

    // Using stdio puts
    start = clock();
    for (i = 0; i < numstr; ++i)
        _putws(strs[i].c_str());
    fflush(stdout);
    stop = clock();
    fprintf(stderr, "stdio puts elapsed: %f\n", (double) (stop - start) / CLOCKS_PER_SEC);

    // Using stdio printf
    start = clock();
    for (i = 0; i < numstr; ++i)
        wprintf(L"%s\n", strs[i].c_str());
    fflush(stdout);
    stop = clock();
    fprintf(stderr, "stdio printf elapsed: %f\n", (double) (stop - start) / CLOCKS_PER_SEC);

    // Using iostream
    start = clock();
    for (i = 0; i < numstr; ++i)
        wcout << strs[i] << L"\n";
    flush(wcout);
    stop = clock();
    fprintf(stderr, "iostream elapsed: %f\n", (double) (stop - start) / CLOCKS_PER_SEC);

    // Using streambuf
    start = clock();
    wstreambuf* osb = wcout.rdbuf();
    for (i = 0; i < numstr; ++i) {
        osb->sputn(strs[i].c_str(), lenstr);
        osb->sputc(L'\n');
    }
    flush(wcout);
    stop = clock();
    fprintf(stderr, "streambuf elapsed: %f\n", (double) (stop - start) / CLOCKS_PER_SEC);
}

////////////////////////////////////////////////////////////////////////////////
// Setup and Cleanup
////////////////////////////////////////////////////////////////////////////////

bool setup()
{
    setlocale(LC_ALL, "");
    srand((unsigned) time(NULL));
    return true;
}

void cleanup()
{
    dbg_fputs("Press any key to Exit...\n", stderr);
    dbg_getch();
}

////////////////////////////////////////////////////////////////////////////////
// Command-line Options
////////////////////////////////////////////////////////////////////////////////

struct ProgramOptions
{
    static const unsigned NUM_STR   = 10;
    static const unsigned LEN_STR   = 64;

    static const char OPT_NUM_STR[];
    static const char OPT_LEN_STR[];
    static const char OPT_STDIO_SYNC[];

    unsigned NumStr;
    unsigned LenStr;
    bool SyncStdio;

    // Valid options:
    // program -n:<numstr> -l:<lenstr> -s:{0|1}
    ProgramOptions(int argc, char* argv[]) :
        NumStr(NUM_STR), LenStr(LEN_STR), SyncStdio(true)
    {
        char *ctx, *tok, *oldtok;
        for (int i = 1; i < argc; ++i) {
            tok = strtok_s(argv[i], ":", &ctx);
            if (tok != NULL) {
                oldtok = tok;
                tok = strtok_s(NULL, ":", &ctx);
                if (tok != NULL) {
                    if (!strcmp(oldtok, OPT_NUM_STR))
                        NumStr = atoi(tok);
                    else if (!strcmp(oldtok, OPT_LEN_STR))
                        LenStr = atoi(tok);
                    else if (!strcmp(oldtok, OPT_STDIO_SYNC))
                        SyncStdio = (atoi(tok) != 0);
                    else goto badopt;
                }
                else goto badopt;
            }
        }
        return;

    badopt:
        fprintf(stderr, "Bad option: %s\n", oldtok);
        exit(-1);
    }
};

const char ProgramOptions::OPT_NUM_STR[]    = "-n";
const char ProgramOptions::OPT_LEN_STR[]    = "-l";
const char ProgramOptions::OPT_STDIO_SYNC[] = "-s";

////////////////////////////////////////////////////////////////////////////////
// Entry Point
////////////////////////////////////////////////////////////////////////////////

// Return value:
// 0    Successful
// -1   Setup failed
int main(int argc, char* argv[])
{
    if (!setup()) {
        fprintf(stderr, "%s: Setup failed.\n", PROGRAM_NAME);
        cleanup();
        return -1;
    }

    ProgramOptions opts(argc, argv);
    fprintf(stderr,
           "Number of strings: %u\n"
           "Length of string: %u\n"
           "Sync of stdio: %s\n\n",
           opts.NumStr, opts.LenStr, (opts.SyncStdio ? "on" : "off"));

    // 经测试, 关闭 iostream 与 stdio 的同步, 不会对 MSVCRT 9.0 iostream 的效率有明显提升
    // To output CJK characters properly in iostream of wchar_t in MinGW,
    // requires calling setlocale and closing the sync between iostream (C++) and stdio (C).
    std::ios_base::sync_with_stdio(opts.SyncStdio);

    test_streambuf_iterator(false);
    test_streambuf(false);
    bench_iostream(true, opts.NumStr, opts.LenStr);

    cleanup();
    return 0;
}
