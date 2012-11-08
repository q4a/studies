// PersistWnd.h : main header file for the PersistWnd application
//
#pragma once

#ifndef __AFXWIN_H__
#error "include 'StdAfx.h' before including this file for PCH"
#endif

#include "Resource.h"       // main symbols

////////////////////////////////////////////////////////////////////////////////
// 全局量
////////////////////////////////////////////////////////////////////////////////

#undef MODULE_NAME
#define MODULE_NAME     "PersistWnd"    // 程序模块名

#define BUF_SIZE        256             // 常用缓冲区大小

////////////////////////////////////////////////////////////////////////////////
// 调试功能
////////////////////////////////////////////////////////////////////////////////

// 以 "模块名!函数名:" 形式输出调试报告
#define FMT(fmt)    _T(MODULE_NAME) _T("!") _T(__FUNCTION__) _T(": ")  _T(fmt) _T("\n")
#define FMTA(fmt)   MODULE_NAME "!" __FUNCTION__ ": " fmt "\n"

#define MYTRACE(fmt, ...)   TRACE(FMT(fmt), __VA_ARGS__)
#define MYTRACEA(fmt, ...)  TRACE(FMTA(fmt), __VA_ARGS__)

// CPersistWndApp:
// See PersistWnd.cpp for the implementation of this class
//

class CPersistWndApp : public CWinApp {
public:
    CPersistWndApp();


// Overrides
public:
    virtual BOOL InitInstance();

// Implementation
    afx_msg void OnAppAbout();
    DECLARE_MESSAGE_MAP()
};

extern CPersistWndApp theApp;