// ScrollWnd.h : ScrollWnd 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
#error "在包含此文件之前包含“StdAfx.h”以生成 PCH 文件"
#endif

#include "Resource.h"       // 主符号

// CScrollWndApp:
// 有关此类的实现，请参阅 ScrollWnd.cpp
//

class CScrollWndApp : public CWinApp {
public:
    CScrollWndApp();

// 重写
public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();

// 实现
    afx_msg void OnAppAbout();
    DECLARE_MESSAGE_MAP()

};

extern CScrollWndApp g_TheApp;
