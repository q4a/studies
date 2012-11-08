// PersistFrm.cpp : implementation of the CPersistFrame class
//

#include "StdAfx.h"

#include "PersistFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPersistFrame

IMPLEMENT_DYNCREATE(CPersistFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CPersistFrame, CFrameWnd)
    ON_WM_DESTROY()
END_MESSAGE_MAP()

const CRect CPersistFrame::RectDefault = CRect(10, 10, 500, 400);
LPCTSTR CPersistFrame::ProfileHeading = _T("Window Size");
LPCTSTR CPersistFrame::ProfileRect = _T("rect");
LPCTSTR CPersistFrame::ProfileMin = _T("min");
LPCTSTR CPersistFrame::ProfileMax = _T("max");

// CPersistFrame construction/destruction

CPersistFrame::CPersistFrame() : m_FirstActive(TRUE)
{
}

CPersistFrame::~CPersistFrame()
{
}

BOOL CPersistFrame::PreCreateWindow(CREATESTRUCT& cs)
{
    if( !CFrameWnd::PreCreateWindow(cs) )
        return FALSE;
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs

    return TRUE;
}


// CPersistFrame diagnostics

#ifdef _DEBUG
void CPersistFrame::AssertValid() const
{
    CFrameWnd::AssertValid();
}

void CPersistFrame::Dump(CDumpContext& dc) const
{
    CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CPersistFrame message handlers

void CPersistFrame::ActivateFrame(int nCmdShow)
{
    CString str;
    BOOL minimized, maximized;
    UINT flag;
    CRect rect;
    WINDOWPLACEMENT wndpl;

    if (m_FirstActive) {
        m_FirstActive = FALSE;
        str = AfxGetApp()->GetProfileString(ProfileHeading, ProfileRect);
        if (!str.IsEmpty()) {
            rect.left = _tstoi((LPCTSTR) str);
            rect.top = _tstoi((LPCTSTR) str + 5);
            rect.right = _tstoi((LPCTSTR) str + 10);
            rect.bottom = _tstoi((LPCTSTR) str + 15);
        }
        else
            rect = RectDefault;

        minimized = AfxGetApp()->GetProfileInt(ProfileHeading, ProfileMin, 0);
        maximized = AfxGetApp()->GetProfileInt(ProfileHeading, ProfileMax, 0);

        if (minimized) {
            nCmdShow = SW_SHOWMINNOACTIVE;
            flag = (maximized ? WPF_RESTORETOMAXIMIZED : WPF_SETMINPOSITION);
        }
        else {
            if (maximized) {
                nCmdShow = SW_SHOWMAXIMIZED;
                flag = WPF_RESTORETOMAXIMIZED;
            }
            else {
                nCmdShow = SW_NORMAL;
                flag = WPF_SETMINPOSITION;
            }
        }

        wndpl.length = sizeof(WINDOWPLACEMENT);
        wndpl.showCmd = nCmdShow;
        wndpl.flags = flag;
        wndpl.ptMinPosition = CPoint(0, 0);
        wndpl.ptMaxPosition = CPoint(-::GetSystemMetrics(SM_CXBORDER), -::GetSystemMetrics(SM_CYBORDER));
        wndpl.rcNormalPosition = rect;
        LoadBarState(AfxGetApp()->m_pszProfileName);

        // sets window's position and minimized/maximized status
        BOOL ret = SetWindowPlacement(&wndpl);
    }

    CFrameWnd::ActivateFrame(nCmdShow);
}

void CPersistFrame::OnDestroy()
{
    BOOL minimized, maximized;
    WINDOWPLACEMENT wndpl;
    wndpl.length = sizeof(WINDOWPLACEMENT);

    // Gets current window position and minimized/maximized status
    BOOL ret = GetWindowPlacement(&wndpl);
    if (wndpl.showCmd == SW_SHOWNORMAL) {
        minimized = FALSE;
        maximized = FALSE;
    }
    else if (wndpl.showCmd == SW_SHOWMAXIMIZED) {
        minimized = FALSE;
        maximized = TRUE;
    }
    else if (wndpl.showCmd == SW_SHOWMINIMIZED) {
        minimized = TRUE;
        maximized = (wndpl.flags != 0);
    }

    CString str;
    str.Format(_T("%04d %04d %04d %04d"), wndpl.rcNormalPosition.left, wndpl.rcNormalPosition.top, wndpl.rcNormalPosition.right, wndpl.rcNormalPosition.bottom);
    AfxGetApp()->WriteProfileString(ProfileHeading, ProfileRect, str);
    AfxGetApp()->WriteProfileInt(ProfileHeading, ProfileMin, minimized);
    AfxGetApp()->WriteProfileInt(ProfileHeading, ProfileMax, maximized);
    SaveBarState(AfxGetApp()->m_pszProfileName);

    CFrameWnd::OnDestroy();
}
