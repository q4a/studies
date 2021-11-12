// StdAfx.h
//

#pragma once

// ָ��Ŀ�� Windows �汾�����ַ���:
// 1. ���� SDKDDKVer.h, �ٶ�Ŀ��ƽ̨�Ϳ���ƽ̨�İ汾��ͬ
//    Ҫ��: VC 2010 (_MSC_VER = 1600) ֮ǰ��Ҫ���� Windows SDK Ŀ¼
// 2. ָ�� _WIN32_WINNT �Ȱ汾���ƺ�, Ȼ���ѡ����� SDKDDKVer.h
//    Ҫ��: ���ϵ�Ŀ�� Windows ��Ҫ�Ȱ��� WinSDKVer.h

#if _MSC_VER < 1600
#ifndef WINVER
#define WINVER          0x0501  // Windows XP+ ����
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT    0x0501  // Windows XP+ ����
#endif

#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS  0x0410  // Windows 98+ ����
#endif

#ifndef _WIN32_IE
#define _WIN32_IE       0x0600  // IE 6.0+ ����
#endif
#endif  // _MSC_VER < 1600

#if _MSC_VER >= 1600
#include <SDKDDKVer.h>
#endif

////////////////////////////////////////////////////////////////////////////////
// C ��׼��������ʱ�� (CRT)
////////////////////////////////////////////////////////////////////////////////

// #define _CRT_SECURE_NO_WARNINGS     // �رղ���ȫ�� CRT ��������
#define _USE_MATH_DEFINES           // ʹ�� math.h �е� M_PI �ȳ���
#define _CRTDBG_MAP_ALLOC           // ʹ�� Debug ��� malloc �� strdup
#define _CRT_RAND_S                 // ʹ������������� rand_s

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
// C++ ��׼��
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

// VC 2005 ʹ�� _CRTDBG_MAP_ALLOC ���� Debug �� free ��ʱ, �� valarray �� free ��Ա���ֳ�ͻ
#if _MSC_VER >= 1600 || !defined(_CRTDBG_MAP_ALLOC)
#include <valarray>
#endif

#include <iterator>
#include <algorithm>
#include <functional>

////////////////////////////////////////////////////////////////////////////////
// Windows API
////////////////////////////////////////////////////////////////////////////////

// �ų� Windows ͷ�ļ��в����õĹ���
#define WIN32_LEAN_AND_MEAN

// ��ʹ�� Windows ͷ�ļ��ж���� min, max ��, ����Ӱ�� std ���ֿռ�� min, max
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
