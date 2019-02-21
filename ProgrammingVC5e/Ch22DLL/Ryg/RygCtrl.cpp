// RygCtrl.cpp : implementation file
//

#include "StdAfx.h"
#include "Ryg.h"
#include "RygCtrl.h"


// CRygCtrl

CRect CRygCtrl::RectRnd(-500, 1000,500, -1000);

CPoint CRygCtrl::Point(300, 300);

CRect CRygCtrl::RectColor[3] = {
    CRect(-250, 800, 250, 300),
    CRect(-250, 250, 250, -250),
    CRect(-250, -300, 250, -800)
};

CBrush CRygCtrl::BrushColor[4] = {
    RGB(192, 192, 192),
    RGB(255, 0, 0),
    RGB(255, 255, 0),
    RGB(0, 255, 0)
};

LPCTSTR CRygCtrl::ClassName = _T("RYGCtrl");

IMPLEMENT_DYNAMIC(CRygCtrl, CWnd)

BEGIN_MESSAGE_MAP(CRygCtrl, CWnd)
    ON_WM_PAINT()
    ON_WM_LBUTTONDOWN()
    ON_MESSAGE(WM_RYG_SETSTATE, OnSetState)
    ON_MESSAGE(WM_RYG_GETSTATE, OnGetState)
END_MESSAGE_MAP()

CRygCtrl::CRygCtrl() : m_State(RYG_OFF)
{
    MYTRACE("Enter");
}

CRygCtrl::~CRygCtrl()
{
    MYTRACE("Enter");
}

LRESULT CALLBACK AFX_EXPORT CRygCtrl::RygWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    CWnd* wnd = CWnd::FromHandlePermanent(hwnd);
    if (wnd == NULL) {
        // Assume that client created a CRygCtrl window
        wnd = new CRygCtrl;
        wnd->Attach(hwnd);
    }
    ASSERT(wnd->m_hWnd == hwnd);
    ASSERT(wnd == CWnd::FromHandlePermanent(hwnd));
    LRESULT res = AfxCallWndProc(wnd, hwnd, msg, wparam, lparam);
    return res;
}

BOOL CRygCtrl::RegisterClass(HINSTANCE inst)
{
    WNDCLASS wc;
    wc.lpszClassName = ClassName;
    wc.hInstance = inst;
    wc.lpfnWndProc = RygWndProc;
    wc.hCursor = ::LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = NULL;
    wc.lpszMenuName = NULL;
    wc.hbrBackground = (HBRUSH) ::GetStockObject(LTGRAY_BRUSH);
    wc.style = CS_GLOBALCLASS;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    return (::RegisterClass(&wc) != 0);
}

void CRygCtrl::SetMapping(CDC* dc)
{
    CRect clientRect;
    GetClientRect(clientRect);
    dc->SetMapMode(MM_ISOTROPIC);
    dc->SetWindowExt(1000, 2000);
    dc->SetViewportExt(clientRect.right, -clientRect.bottom);
    dc->SetViewportOrg(clientRect.right / 2, clientRect.bottom / 2);
}

void CRygCtrl::UpdateColor(CDC* pDC, int n)
{
    if (m_State == n + 1)
        pDC->SelectObject(&BrushColor[n+1]);
    else
        pDC->SelectObject(&BrushColor[0]);
    pDC->Ellipse(RectColor[n]);
}

// CRygCtrl message handlers

void CRygCtrl::OnPaint()
{
    CPaintDC dc(this);
    SetMapping(&dc);
    dc.SelectStockObject(DKGRAY_BRUSH);
    dc.RoundRect(RectRnd, Point);
    for (int i = 0; i < 3; i++)
        UpdateColor(&dc, i);
}

void CRygCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
    GetParent()->SendMessage(WM_COMMAND, GetDlgCtrlID(), (LPARAM) GetSafeHwnd());
}

void CRygCtrl::PostNcDestroy()
{
    MYTRACE("Enter");
    delete this;
}

LRESULT CRygCtrl::OnSetState(WPARAM wparam, LPARAM lparam)
{
    MYTRACE("wparam = %d\n", wparam);
    m_State = (RYG_STAT) wparam;
    Invalidate(FALSE);
    return 0;
}

LRESULT CRygCtrl::OnGetState(WPARAM wparam, LPARAM lparam)
{
    MYTRACE("Enter");
    return m_State;
}
