// Depends.h
//

#pragma once

////////////////////////////////////////////////////////////////////////////////
// C 标准库与运行时库 (CRT)
////////////////////////////////////////////////////////////////////////////////

// #define _CRT_SECURE_NO_WARNINGS     // 关闭不安全的 CRT 函数警告
#define _USE_MATH_DEFINES           // 使用 math.h 中的 M_PI 等常量
#define _CRTDBG_MAP_ALLOC           // 使用 Debug 版的 malloc 和 strdup

#include <stdlib.h>
#include <errno.h>
#include <crtdbg.h>
#include <time.h>

#include <stdio.h>
#include <conio.h>

#include <limits.h>
#include <float.h>
#include <math.h>

#include <locale.h>
#include <ctype.h>
#include <string.h>
#include <mbstring.h>
#include <wchar.h>
#include <tchar.h>

#include <sal.h>
#include <direct.h>
#include <typeinfo.h>
#include <sys/types.h>
#include <sys/stat.h>

////////////////////////////////////////////////////////////////////////////////
// C++ 标准库
////////////////////////////////////////////////////////////////////////////////

#include <ios>
#include <iostream>
#include <istream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <iomanip>

#include <exception>
#include <stdexcept>

#include <locale>
#include <utility>
#include <numeric>
#include <typeinfo>

#include <memory>
#include <new>

#include <string>
#include <vector>
#include <list>
#include <deque>
#include <bitset>
#include <map>
#include <set>
#include <queue>
#include <stack>

#include <iterator>
#include <algorithm>
#include <functional>

////////////////////////////////////////////////////////////////////////////////
// Windows API
////////////////////////////////////////////////////////////////////////////////

// 排除 Windows 头文件中不常用的功能
#define WIN32_LEAN_AND_MEAN

// 不使用 Windows 头文件中定义的 min, max 宏, 它会影响 std 名字空间的 min, max
#define NOMINMAX

#include <Windows.h>

////////////////////////////////////////////////////////////////////////////////
// Simp
////////////////////////////////////////////////////////////////////////////////

#include <Simp/Defs.h>
#include <Simp/Memory.h>
#include <Simp/Debug.h>
#include <Simp/Utility.h>
#include <Simp/String.h>
#include <Simp/Stream.h>
#include <Simp/Thread.h>
#include <Simp/Log.h>
#include <Simp/File.h>
#include <Simp/Path.h>
