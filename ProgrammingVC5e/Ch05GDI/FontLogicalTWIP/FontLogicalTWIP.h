// FontLogicalTWIP.h : main header file for the FontLogicalTWIP application
//
#pragma once

#ifndef __AFXWIN_H__
#error "include 'StdAfx.h' before including this file for PCH"
#endif

#include "Resource.h"       // main symbols


// CFontLogicalTWIPApp:
// See FontLogicalTWIP.cpp for the implementation of this class
//

class CFontLogicalTWIPApp : public CWinApp {
public:
    CFontLogicalTWIPApp();


// Overrides
public:
    virtual BOOL InitInstance();

// Implementation
    afx_msg void OnAppAbout();
    DECLARE_MESSAGE_MAP()
};

extern CFontLogicalTWIPApp theApp;