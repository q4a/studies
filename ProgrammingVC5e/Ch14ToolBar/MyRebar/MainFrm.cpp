// MainFrm.cpp : implementation of the CMainFrame class
//

#include "StdAfx.h"
#include "MyRebar.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
    ON_WM_CREATE()
    ON_BN_CLICKED(IDC_BUTTON1, &CMainFrame::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON2, &CMainFrame::OnBnClickedButton2)
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

    if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT | TBSTYLE_TRANSPARENT) ||
            !m_wndToolBar.LoadToolBar(IDR_MAINFRAME)) {
        TRACE0("Failed to create toolbar\n");
        return -1;      // fail to create
    }
    if (!m_wndDlgBar.Create(this, IDR_MAINFRAME,
                            CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR)) {
        TRACE0("Failed to create dialogbar\n");
        return -1;      // fail to create
    }

    if (!m_wndReBar.Create(this) ||
            !m_wndReBar.AddBar(&m_wndToolBar) ||
            !m_wndReBar.AddBar(&m_wndDlgBar)) {
        TRACE0("Failed to create rebar\n");
        return -1;      // fail to create
    }

    if (!m_wndStatusBar.Create(this) ||
            !m_wndStatusBar.SetIndicators(indicators,
                                          sizeof(indicators)/sizeof(UINT))) {
        TRACE0("Failed to create status bar\n");
        return -1;      // fail to create
    }

    // TODO: Remove this if you don't want tool tips
    m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
                             CBRS_TOOLTIPS | CBRS_FLYBY);

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

void CMainFrame::OnBnClickedButton1()
{
    CProgressCtrl* progress = (CProgressCtrl*) m_wndDlgBar.GetDlgItem(IDC_PROGRESS1);
    progress->StepIt();
}

void CMainFrame::OnBnClickedButton2()
{
    CProgressCtrl* progress = (CProgressCtrl*) m_wndDlgBar.GetDlgItem(IDC_PROGRESS1);
    int pos = progress->GetPos() - 10;
    if (pos < 0)
        pos = 0;
    progress->SetPos(pos);
}
