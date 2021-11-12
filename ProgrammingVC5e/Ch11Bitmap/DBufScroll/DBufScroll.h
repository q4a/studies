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
// ȫ����
////////////////////////////////////////////////////////////////////////////////

#define DEFAULT_VIEW_WIDTH  600     // ������Ĭ�Ͽ��, �ӿ�
#define DEFAULT_VIEW_HEIGHT 600     // ������Ĭ�ϸ߶�, �ӿ�
#define DEFAULT_WIDTH       1280    // ���������ܿ��
#define DEFAULT_HEIGHT      1000    // ���������ܸ߶�

extern CDBufScrollApp theApp;