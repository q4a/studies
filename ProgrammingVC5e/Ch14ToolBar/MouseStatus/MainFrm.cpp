// MainFrm.cpp : implementation of the CMainFrame class
//

#include "StdAfx.h"
#include "MouseStatus.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
    ON_WM_CREATE()
    ON_COMMAND(ID_VIEW_STATUS_BAR, &CMainFrame::OnViewStatusBar)
    ON_UPDATE_COMMAND_UI(ID_VIEW_STATUS_BAR, &CMainFrame::OnUpdateViewStatusBar)
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_LEFT, &CMainFrame::OnUpdateLeft)
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_RIGHT, &CMainFrame::OnUpdateRight)
END_MESSAGE_MAP()

static UINT indicators[] = {
    ID_SEPARATOR,
    ID_SEPARATOR,
    ID_INDICATOR_LEFT,
    ID_INDICATOR_RIGHT
};


// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
    // TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
                               | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
            !m_wndToolBar.LoadToolBar(IDR_MAINFRAME)) {
        TRACE0("Failed to create toolbar\n");
        return -1;      // fail to create
    }

    if (!m_wndStatusBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_BOTTOM, ID_MY_STATUS_BAR) ||
            !m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT))) {
        TRACE0("Failed to create status bar\n");
        return -1;      // fail to create
    }

    m_wndStatusBar.SetPaneInfo(0, 0, 0, 50);
    m_wndStatusBar.SetPaneInfo(1, 0, SBPS_STRETCH, 50);

    // TODO: Delete these three lines if you don't want the toolbar to be dockable
    m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
    EnableDocking(CBRS_ALIGN_ANY);
    DockControlBar(&m_wndToolBar);

    return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
    if( !CFrameWnd::PreCreateWindow(cs) )
        return FALSE;
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs

    return TRUE;
}


// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
    CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
    CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnViewStatusBar()
{
    m_wndStatusBar.ShowWindow((m_wndStatusBar.GetStyle() & WS_VISIBLE) ? SW_HIDE : SW_NORMAL);
    RecalcLayout(TRUE);
}

void CMainFrame::OnUpdateViewStatusBar(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck(m_wndStatusBar.GetStyle() & WS_VISIBLE);
}

void CMainFrame::OnUpdateLeft(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(::GetKeyState(VK_LBUTTON) < 0);
}

void CMainFrame::OnUpdateRight(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(::GetKeyState(VK_RBUTTON) < 0);
}
