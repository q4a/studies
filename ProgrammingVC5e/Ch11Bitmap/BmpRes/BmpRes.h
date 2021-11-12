// BmpRes.h : main header file for the BmpRes application
//
#pragma once

#ifndef __AFXWIN_H__
#error "include 'StdAfx.h' before including this file for PCH"
#endif

#include "Resource.h"       // main symbols


// CBmpResApp:
// See BmpRes.cpp for the implementation of this class
//

class CBmpResApp : public CWinApp {
public:
    CBmpResApp();


// Overrides
public:
    virtual BOOL InitInstance();

// Implementation
    afx_msg void OnAppAbout();
    DECLARE_MESSAGE_MAP()
};

extern CBmpResApp theApp;