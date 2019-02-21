// MainFrm.cpp : implementation of the CMainFrame class
//

#include "StdAfx.h"
#include "PoemSwitch.h"

#include "PoemDoc.h"
#include "StringView.h"
#include "HexView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
    ON_WM_CREATE()
    ON_COMMAND(ID_VIEW_STRINGVIEW, &CMainFrame::OnViewStringView)
    ON_UPDATE_COMMAND_UI(ID_VIEW_STRINGVIEW, &CMainFrame::OnUpdateViewStringView)
    ON_COMMAND(ID_VIEW_HEXVIEW, &CMainFrame::OnViewHexView)
    ON_UPDATE_COMMAND_UI(ID_VIEW_HEXVIEW, &CMainFrame::OnUpdateViewHexView)
END_MESSAGE_MAP()

static UINT indicators[] = {
    ID_SEPARATOR,           // status line indicator
    ID_INDICATOR_CAPS,
    ID_INDICATOR_NUM,
    ID_INDICATOR_SCRL,
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

    if (!m_wndStatusBar.Create(this) ||
            !m_wndStatusBar.SetIndicators(indicators,
                                          sizeof(indicators)/sizeof(UINT))) {
        TRACE0("Failed to create status bar\n");
        return -1;      // fail to create
    }

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

void CMainFrame::SwitchToView(VIEW_TYPE viewType)
{
    ASSERT(viewType == VIEW_STRING || viewType == VIEW_HEX);

    CView* oldView = GetActiveView();
    CView* newView = (CView*) GetDlgItem(viewType);

    if (newView == NULL) {
        if (viewType == VIEW_STRING)
            newView = new CStringView;
        else if (viewType == VIEW_HEX)
            newView = new CHexView;

        CCreateContext ctx;
        ctx.m_pCurrentDoc = oldView->GetDocument();
        newView->Create(NULL, NULL, WS_BORDER, CFrameWnd::rectDefault, this, viewType, &ctx);
        newView->OnInitialUpdate();
    }

    SetActiveView(newView);
    oldView->ShowWindow(SW_HIDE);
    oldView->SetDlgCtrlID(oldView->GetRuntimeClass() == RUNTIME_CLASS(CStringView) ? VIEW_STRING : VIEW_HEX);
    newView->ShowWindow(SW_SHOW);
    newView->SetDlgCtrlID(AFX_IDW_PANE_FIRST);
    RecalcLayout(TRUE);
}

// CMainFrame message handlers

void CMainFrame::OnViewStringView()
{
    SwitchToView(VIEW_STRING);
}

void CMainFrame::OnUpdateViewStringView(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(!GetActiveView()->IsKindOf(RUNTIME_CLASS(CStringView)));
}

void CMainFrame::OnViewHexView()
{
    SwitchToView(VIEW_HEX);
}

void CMainFrame::OnUpdateViewHexView(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(!GetActiveView()->IsKindOf(RUNTIME_CLASS(CHexView)));
}
