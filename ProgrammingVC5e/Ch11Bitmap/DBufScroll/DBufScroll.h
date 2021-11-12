// DBufScroll.h : main header file for the DBufScroll application
//
#pragma once

#ifndef __AFXWIN_H__
#error "include 'StdAfx.h' before including this file for PCH"
#endif

#include "Resource.h"       // main symbols

// CDBufScrollApp:
// See DBufScroll.cpp for the implementation of this class
//

class CDBufScrollApp : public CWinApp {
public:
    CDBufScrollApp();

// Overrides
public:
    virtual BOOL InitInstance();

// Implementation
    afx_msg void OnAppAbout();
    DECLARE_MESSAGE_MAP()
};

////////////////////////////////////////////////////////////////////////////////
// 全局量
////////////////////////////////////////////////////////////////////////////////

#define DEFAULT_VIEW_WIDTH  600     // 主窗口默认宽度, 视口
#define DEFAULT_VIEW_HEIGHT 600     // 主窗口默认高度, 视口
#define DEFAULT_WIDTH       1280    // 滚动窗口总宽度
#define DEFAULT_HEIGHT      1000    // 滚动窗口总高度

extern CDBufScrollApp theApp;