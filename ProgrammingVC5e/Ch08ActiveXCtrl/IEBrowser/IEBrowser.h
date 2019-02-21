// IEBrowser.h : main header file for the IEBrowser application
//
#pragma once

#ifndef __AFXWIN_H__
#error "include 'StdAfx.h' before including this file for PCH"
#endif

#include "Resource.h"       // main symbols

#define DEFAULT_URL     "http://localhost/"

// CIEBrowserApp:
// See IEBrowser.cpp for the implementation of this class
//

class CIEBrowserApp : public CWinApp {
public:
    CIEBrowserApp();


// Overrides
public:
    virtual BOOL InitInstance();

// Implementation
    afx_msg void OnAppAbout();
    DECLARE_MESSAGE_MAP()
};

extern CIEBrowserApp theApp;