// Depends.h
//

#ifndef __DEPENDS_H__
#define __DEPENDS_H__

////////////////////////////////////////////////////////////////////////////////
// C 标准库与运行时库 (CRT)
////////////////////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS     // 关闭不安全的 CRT 函数警告
#define _CRTDBG_MAP_ALLOC           // 使用 Debug 版的 malloc 和 strdup

#include <stddef.h>
#include <stdlib.h>

#include <errno.h>
#include <crtdbg.h>

#include <stdio.h>

#include <string.h>
#include <mbstring.h>
#include <wchar.h>
#include <tchar.h>
#include <locale.h>

#include <sal.h>
#include <typeinfo.h>

////////////////////////////////////////////////////////////////////////////////
// C++ 标准库
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <sstream>

#include <exception>
#include <stdexcept>

#include <new>
#include <locale>

#include <string>
#include <vector>
#include <list>
#include <deque>

////////////////////////////////////////////////////////////////////////////////
// Windows API
////////////////////////////////////////////////////////////////////////////////

// 排除 Windows 头文件中不常用的功能
#define WIN32_LEAN_AND_MEAN

// 不使用 Windows 头文件中定义的 min, max 宏, 它会影响 std 名字空间的 min, max
// #define NOMINMAX

// 使用 MFC 库时不要包含 Windows.h, MFC 头文件中已包含
// #include <Windows.h>

// Windows 通用控件 ComCtl32.dll 版本 6.0 的内嵌 manifest
#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif  // _UNICODE

////////////////////////////////////////////////////////////////////////////////
// MFC
////////////////////////////////////////////////////////////////////////////////

// 排除 Windows 头文件中不常用的功能, 适用于 MFC
#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN
#endif

// ATL/MFC 的安全设置
#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS  // 使 ATL/MFC 的 CString 具有显式地构造函数 (explicit)
#define _AFX_ALL_WARNINGS                   // 打开 MFC 的所有警告, 包括一般可以安全忽略的警告

#include <afxwin.h>     // MFC 核心和标准支持
#include <afxext.h>     // MFC 扩展支持
#include <afxmt.h>      // MFC 多线程扩展和同步对象

#include <atlimage.h>   // CImage

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>   // MFC 的 IE 4 通用控件支持
#endif

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>     // MFC 的 Windows 通用控件支持
#endif

#endif  // __DEPENDS_H__
