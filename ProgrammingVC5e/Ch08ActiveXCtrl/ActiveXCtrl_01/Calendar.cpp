// CCalendar.cpp  : Definition of ActiveX Control wrapper class(es) created by Microsoft Visual C++


#include "StdAfx.h"
#include "Calendar.h"

/////////////////////////////////////////////////////////////////////////////
// CCalendar

IMPLEMENT_DYNCREATE(CCalendar, CWnd)

LPCTSTR CCalendar::s_HelpFilePath = _T("D:\\source\\cpp\\test\\StudyMFC\\COM\\MSCal\\MSCAL.HLP");

// CCalendar properties

// CCalendar operations
BEGIN_MESSAGE_MAP(CCalendar, CWnd)
    ON_WM_HELPINFO()
END_MESSAGE_MAP()

BOOL CCalendar::OnHelpInfo(HELPINFO* pHelpInfo)
{
    // ��Ҫ���û���� OnHelpInfo()������Ĭ�ϴ򿪹���Ŀ¼�º͹�������ͬ�� .hlp �ļ�
    // CWnd::OnHelpInfo(pHelpInfo);

    ::WinHelp(this->GetSafeHwnd(), s_HelpFilePath, HELP_FINDER, 0);

    return FALSE;
}
