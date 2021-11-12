// PersistWnd.h : main header file for the PersistWnd application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'StdAfx.h' before including this file for PCH"
#endif

#include "Resource.h"       // main symbols


// CPersistWndApp:
// See PersistWnd.cpp for the implementation of this class
//

class CPersistWndApp : public CWinApp
{
public:
	CPersistWndApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPersistWndApp theApp;