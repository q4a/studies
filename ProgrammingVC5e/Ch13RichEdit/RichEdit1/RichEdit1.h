// RichEdit1.h : main header file for the RichEdit1 application
//
#pragma once

#ifndef __AFXWIN_H__
#error "include 'StdAfx.h' before including this file for PCH"
#endif

#include "Resource.h"       // main symbols


// CRichEdit1App:
// See RichEdit1.cpp for the implementation of this class
//

class CRichEdit1App : public CWinApp {
public:
    CRichEdit1App();


// Overrides
public:
    virtual BOOL InitInstance();

// Implementation
    afx_msg void OnAppAbout();
    DECLARE_MESSAGE_MAP()
};

////////////////////////////////////////////////////////////////////////////////
// ȫ������
////////////////////////////////////////////////////////////////////////////////

#undef MODULE_NAME
#define MODULE_NAME     "RichEdit1"     // ����ģ����

#define BUF_SIZE        256             // ���û�������С

extern CRichEdit1App    RichEdit1App;   // Ӧ�ó���ʵ��

////////////////////////////////////////////////////////////////////////////////
// ���Թ���
////////////////////////////////////////////////////////////////////////////////

// Debug �� new
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// �� "ģ����!������:" ��ʽ������Ա���
#define FMT(fmt)                _T(MODULE_NAME) _T("!") _T(__FUNCTION__) _T(": ")  _T(fmt) _T("\n")
#define FMTA(fmt)               MODULE_NAME "!" __FUNCTION__ ": " fmt "\n"

#define MYTRACE(fmt, ...)       TRACE(FMT(fmt), __VA_ARGS__)
#define MYTRACEA(fmt, ...)      TRACE(FMTA(fmt), __VA_ARGS__)

#define TRACE_FAIL(func, err)   MYTRACE("%s failed: %ld", _T(func), err)
#define TRACE_FAILA(func, err)  MYTRACEA("%s failed: %ld", func, err)

#define FAILED_DO(hr, exp)      if (FAILED(hr)) { exp; }
