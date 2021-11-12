// StudentForm2.h : main header file for the StudentForm2 application
//
#pragma once

#ifndef __AFXWIN_H__
#error "include 'StdAfx.h' before including this file for PCH"
#endif

#include "Resource.h"       // main symbols

////////////////////////////////////////////////////////////////////////////////
// ȫ����
////////////////////////////////////////////////////////////////////////////////

#undef MODULE_NAME
#define MODULE_NAME     "StudentForm2"  // ����ģ����

#define BUF_SIZE        256         // ���û�������С

////////////////////////////////////////////////////////////////////////////////
// ���Թ���
////////////////////////////////////////////////////////////////////////////////

// �� "ģ����!������:" ��ʽ������Ա���
#define FMT(fmt)    _T(MODULE_NAME) _T("!") _T(__FUNCTION__) _T(": ")  _T(fmt) _T("\n")
#define FMTA(fmt)   MODULE_NAME "!" __FUNCTION__ ": " fmt "\n"

#define MYTRACE(fmt, ...)   TRACE(FMT(fmt), __VA_ARGS__)
#define MYTRACEA(fmt, ...)  TRACE(FMTA(fmt), __VA_ARGS__)

// CStudentForm2App:
// See StudentForm2.cpp for the implementation of this class
//

class CStudentForm2App : public CWinApp {
public:
    CStudentForm2App();


// Overrides
public:
    virtual BOOL InitInstance();

// Implementation
    afx_msg void OnAppAbout();
    DECLARE_MESSAGE_MAP()
};

extern CStudentForm2App theApp;
