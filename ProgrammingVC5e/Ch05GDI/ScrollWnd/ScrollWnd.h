// ScrollWnd.h : ScrollWnd Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
#error "�ڰ������ļ�֮ǰ������StdAfx.h�������� PCH �ļ�"
#endif

#include "Resource.h"       // ������

// CScrollWndApp:
// �йش����ʵ�֣������ ScrollWnd.cpp
//

class CScrollWndApp : public CWinApp {
public:
    CScrollWndApp();

// ��д
public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();

// ʵ��
    afx_msg void OnAppAbout();
    DECLARE_MESSAGE_MAP()

};

extern CScrollWndApp g_TheApp;
