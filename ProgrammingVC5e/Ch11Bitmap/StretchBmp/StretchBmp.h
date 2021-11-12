// StretchBmp.h : main header file for the StretchBmp application
//
#pragma once

#ifndef __AFXWIN_H__
#error "include 'StdAfx.h' before including this file for PCH"
#endif

#include "Resource.h"       // main symbols


// CStretchBmpApp:
// See StretchBmp.cpp for the implementation of this class
//

class CStretchBmpApp : public CWinApp {
public:
    CStretchBmpApp();


// Overrides
public:
    virtual BOOL InitInstance();

// Implementation
    afx_msg void OnAppAbout();
    DECLARE_MESSAGE_MAP()
};

extern CStretchBmpApp theApp;
