// StudentForm.h : main header file for the StudentForm application
//
#pragma once

#ifndef __AFXWIN_H__
#error "include 'StdAfx.h' before including this file for PCH"
#endif

#include "Resource.h"       // main symbols


// CStudentFormApp:
// See StudentForm.cpp for the implementation of this class
//

class CStudentFormApp : public CWinApp {
public:
    CStudentFormApp();


// Overrides
public:
    virtual BOOL InitInstance();

// Implementation
    afx_msg void OnAppAbout();
    DECLARE_MESSAGE_MAP()
};

extern CStudentFormApp theApp;