// Ryg.h : main header file for the Ryg DLL
//

#pragma once

#ifndef __AFXWIN_H__
#error "include 'StdAfx.h' before including this file for PCH"
#endif

#include "Resource.h"		// main symbols

#ifdef _RYG_EXPORT
#define RYG_API __declspec(dllexport)
#else
#define RYG_API __declspec(dllimport)
#endif  // _RYG_EXPORT

////////////////////////////////////////////////////////////////////////////////
// 全局量
////////////////////////////////////////////////////////////////////////////////

#ifdef _RYG_EXPORT
#undef MODULE_NAME
#define MODULE_NAME     "Ryg"   // 程序模块名
#endif

////////////////////////////////////////////////////////////////////////////////
// 调试功能
////////////////////////////////////////////////////////////////////////////////

#ifdef _RYG_EXPORT

// 以 "模块名!函数名:" 形式输出调试报告
#define FMT(fmt)    _T(MODULE_NAME) _T("!") _T(__FUNCTION__) _T(": ")  _T(fmt) _T("\n")
#define FMTA(fmt)   MODULE_NAME "!" __FUNCTION__ ": " fmt "\n"

#define MYTRACE(fmt, ...)   TRACE(FMT(fmt), __VA_ARGS__)
#define MYTRACEA(fmt, ...)  TRACE(FMTA(fmt), __VA_ARGS__)

#endif  // _RYG_EXPORT

RYG_API void LoadRyg(); // dummy function

// CRygApp
// See Ryg.cpp for the implementation of this class
//

class CRygApp : public CWinApp {
public:
    CRygApp();

// Overrides
public:
    virtual BOOL InitInstance();

    DECLARE_MESSAGE_MAP()
};
