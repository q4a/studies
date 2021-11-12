////////////////////////////////////////////////////////////////////////////////
// 文    件 : MainFrame.cpp
// 功能说明 :
//   主框架窗口
//
// 版    本 : 1.0
// 作    者 : Breaker Zhao <breaker.zy_AT_gmail>
// 日    期 : 2010-10
////////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "ShowBmp.h"
#include "ClientView.h"
#include "MainFrame.h"

////////////////////////////////////////////////////////////////////////////////
// 主框架窗口类 CMainFrame
////////////////////////////////////////////////////////////////////////////////

// MFC RTTI 支持
IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

// 消息映射
BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
    ON_WM_CREATE()
    ON_WM_SETFOCUS()
    ON_COMMAND(ID_FILE_OPEN, &CMainFrame::OnFileOpen)
    ON_COMMAND(ID_APP_ABOUT, &CMainFrame::OnAppAbout)
END_MESSAGE_MAP()

// 状态栏指示器 (indicator)
UINT CMainFrame::StatusBarInd[] = {
    ID_SEPARATOR,
    ID_INDICATOR_CAPS,
    ID_INDICATOR_NUM,
    ID_INDICATOR_SCRL,
};

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
    if (!CFrameWnd::PreCreateWindow(cs))
        return FALSE;

    cs.dwExStyle &= ~WS_EX_CLIENTEDGE;  // 去掉下沉边框样式 (sunken edge)

    // 设置窗口屏幕居中
    cs.cx = DEFAULT_VIEW_WIDTH;
    cs.cy = DEFAULT_VIEW_HEIGHT;
    cs.y = (GetSystemMetrics(SM_CYSCREEN) - cs.cy) >> 1;
    cs.x = (GetSystemMetrics(SM_CXSCREEN) - cs.cx) >> 1;

    cs.lpszClass = AfxRegisterWndClass(0, 0, 0, AfxGetApp()->LoadIcon(IDR_MAINFRAME));
    return TRUE;
}

int CMainFrame::OnCreate(LPCREATESTRUCT cs)
{
    if (CFrameWnd::OnCreate(cs) == -1)
        return -1;
    if (!CreateClientView() || !CreateToolBar() || !CreateStatusBar())
        return -1;
    return 0;
}

BOOL CMainFrame::CreateStatusBar()
{
    if (!m_StatusBar.Create(this) || !m_StatusBar.SetIndicators(StatusBarInd, _countof(StatusBarInd))) {
        SHOWBMP_TRACE("failed to create status bar");
        return FALSE;
    }
    return TRUE;
}

BOOL CMainFrame::CreateClientView()
{
    // NOTE: AFX_WS_DEFAULT_VIEW 为视图窗口的通用样式
    if (!m_ClientView.Create(0, 0, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, 0)) {
        SHOWBMP_TRACE("failed to create client view");
        return FALSE;
    }
    return TRUE;
}

BOOL CMainFrame::CreateToolBar()
{
    const DWORD TOOLBAR_STYLE = WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC;

    // NOTE: LoadToolBar 只能加载 16 色位图, 如果加载 24bit 位图会显示为黑色
    if (!m_ToolBar.CreateEx(this, TBSTYLE_FLAT, TOOLBAR_STYLE) || !m_ToolBar.LoadToolBar(ID_TOOLBAR)) {
        SHOWBMP_TRACE("failed to create toolbar");
        return FALSE;
    }

    // 为 ToolBar 加载 24bit 位图
    CBitmap bmp;
    BITMAP bm;
    CImageList imgList;
    bmp.LoadBitmap(ID_TOOLBAR);
    bmp.GetBitmap(&bm);
    imgList.Create(bm.bmHeight, bm.bmHeight, ILC_COLOR24, bm.bmWidth / bm.bmHeight, 0);
    imgList.Add(&bmp, (CBitmap*) 0);
    m_ToolBar.GetToolBarCtrl().SetImageList(&imgList);
    imgList.Detach();
    bmp.Detach();

    // 使 ToolBar 变为可停靠的
    m_ToolBar.EnableDocking(CBRS_ALIGN_ANY);
    EnableDocking(CBRS_ALIGN_ANY);
    DockControlBar(&m_ToolBar);

    return TRUE;
}

void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
    // 转发 WM_SETFOCUS 消息到 ClientView
    m_ClientView.SetFocus();
}

void CMainFrame::OnAppAbout()
{
    CAboutDlg dlg;
    dlg.DoModal();
}

void CMainFrame::OnFileOpen()
{
    CString filter;
    filter.LoadString(IDS_OPEN_FILE_FILTER);

    CFileDialog fileDlg(TRUE, 0, 0, OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, filter, this, 0);
    if (fileDlg.DoModal() != IDOK)
        return;

    CString path = fileDlg.GetPathName();
    SHOWBMP_TRACE("path=%s", (const TCHAR*) path);

    CString err;
    if (_taccess_s(path, 4) != 0) {
        _TCHAR buf[BUF_SIZE];
        __tcserror_s(buf, (const _TCHAR*) 0);
        err.Format(_T("Cannot read file: %s\n%s (%d)"), path, buf, errno);
        MessageBox(err, _T("Error"), MB_ICONERROR | MB_OK);
        return;
    }

    if (!m_ClientView.LoadBmp(path)) {
        err.Format(_T("Cannot load bitmap: %s"), path);
        MessageBox(err, _T("Error"), MB_ICONERROR | MB_OK);
    }
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
    // 委托 ClientView 做 WM_COMMAND 消息的处理
    if (m_ClientView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
        return TRUE;
    // ClientView 返回 FALSE 时, 进行默认处理
    return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

////////////////////////////////////////////////////////////////////////////////
// 关于对话框类 CAboutDlg
////////////////////////////////////////////////////////////////////////////////

// 消息映射
BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()
