// FontAutoSize.h : main header file for the FontAutoSize application
//
#pragma once

#ifndef __AFXWIN_H__
#error "include 'StdAfx.h' before including this file for PCH"
#endif

#include "Resource.h"       // main symbols


// CFontAutoSizeApp:
// See FontAutoSize.cpp for the implementation of this class
//

class CFontAutoSizeApp : public CWinApp {
public:
    CFontAutoSizeApp();


// Overrides
public:
    virtual BOOL InitInstance();

// Implementation
    afx_msg void OnAppAbout();
    DECLARE_MESSAGE_MAP()
};

extern CFontAutoSizeApp theApp;