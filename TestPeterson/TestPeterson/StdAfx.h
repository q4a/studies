// StdAfx.h
//

#pragma once

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 特定版本的 Windows 平台的功能
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef WINVER
#define WINVER          0x0501      // Windows XP 或更高版本的功能
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT    0x0501      // Windows XP 或更高版本的功能
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 程序库的头文件
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// C RunTime
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <conio.h>
#include <crtdbg.h>
#include <locale.h>
#include <time.h>
#include <process.h>

// Standard C++
#include <vector>

// MSVC Intrinsics
#include <intrin.h>

// Windows API
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN     // 排除 Windows 头文件中不常用的功能
#endif
#include <Windows.h>
