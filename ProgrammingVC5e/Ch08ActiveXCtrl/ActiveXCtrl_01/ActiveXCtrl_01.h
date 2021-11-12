// ActiveXCtrl_01.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
#error "include 'StdAfx.h' before including this file for PCH"
#endif

#include "Resource.h"   // main symbols
#include "ActiveXCtrl_01_i.h"


// CActiveXCtrlApp:
// See ActiveXCtrl_01.cpp for the implementation of this class
//

class CActiveXCtrlApp : public CWinApp {
public:
    CActiveXCtrlApp();

// Overrides
public:
    virtual BOOL InitInstance();

// Implementation

    DECLARE_MESSAGE_MAP()
public:
    BOOL ExitInstance(void);
};

extern CActiveXCtrlApp theApp;