// StdAfx.h
//

#pragma once

// 指定目标 Windows 版本的两种方法:
// 1. 包含 SDKDDKVer.h, 假定目标平台和开发平台的版本相同
//    要求: VC 2010 (_MSC_VER = 1600) 之前需要配置 Windows SDK 目录
// 2. 指定 _WIN32_WINNT 等版本控制宏, 然后可选择包含 SDKDDKVer.h
//    要求: 较老的目标 Windows 需要先包含 WinSDKVer.h

#if _MSC_VER < 1600
#ifndef WINVER
#define WINVER          0x0501  // Windows XP+ 特性
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT    0x0501  // Windows XP+ 特性
#endif

#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS  0x0410  // Windows 98+ 特性
#endif

#ifndef _WIN32_IE
#define _WIN32_IE       0x0600  // IE 6.0+ 特性
#endif
#endif  // _MSC_VER < 1600

#if _MSC_VER >= 1600
#include <SDKDDKVer.h>
#endif

////////////////////////////////////////////////////////////////////////////////
// C 标准库与运行时库 (CRT)
////////////////////////////////////////////////////////////////////////////////

// #define _CRT_SECURE_NO_WARNINGS     // 关闭不安全的 CRT 函数警告
#define _USE_MATH_DEFINES           // 使用 math.h 中的 M_PI 等常量
#define _CRTDBG_MAP_ALLOC           // 使用 Debug 版的 malloc 和 strdup
#define _CRT_RAND_S                 // 使用随机数产生器 rand_s

#include <stddef.h>
#include <crtdefs.h>
#include <stdlib.h>

#include <errno.h>
#include <crtdbg.h>

#include <stdio.h>
#include <conio.h>
#include <io.h>

#include <limits.h>
#include <float.h>
#include <math.h>

#include <ctype.h>
#include <string.h>
#include <mbstring.h>
#include <wchar.h>
#include <tchar.h>
#include <locale.h>

#include <memory.h>
#include <new.h>
#include <malloc.h>
#include <time.h>
#include <direct.h>
#include <process.h>

#include <stdarg.h>
#include <sal.h>
#include <typeinfo.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <search.h>

#include <intrin.h>

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
#include <limits>
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

// VC 2005 使用 _CRTDBG_MAP_ALLOC 启动 Debug 版 free 宏时, 和 valarray 的 free 成员名字冲突
#if _MSC_VER >= 1600 || !defined(_CRTDBG_MAP_ALLOC)
#include <valarray>
#endif

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
// DirectX
////////////////////////////////////////////////////////////////////////////////

#define DIRECTINPUT_VERSION 0x0800

#include <DxErr.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <xinput.h>
