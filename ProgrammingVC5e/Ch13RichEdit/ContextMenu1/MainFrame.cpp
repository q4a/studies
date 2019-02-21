// MainFrame.cpp
//

#include "StdAfx.h"
#include "ContextMenu1.h"
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
    cs.cx = DEFAULT_WIDTH;
    cs.cy = DEFAULT_HEIGHT;
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
        MYTRACE("failed to create status bar");
        return FALSE;
    }
    return TRUE;
}

BOOL CMainFrame::CreateClientView()
{
    // NOTE: AFX_WS_DEFAULT_VIEW 为视图窗口的通用样式
    if (!m_ClientView.Create(0, 0, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, 0)) {
        MYTRACE("failed to create client view");
        return FALSE;
    }
    return TRUE;
}

BOOL CMainFrame::CreateToolBar()
{
    const DWORD TOOLBAR_STYLE = WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC;

    // NOTE: LoadToolBar 只能加载 16 色 (不是 256 色) 位图, 如果加载 8bit 以上位图会有显示问题
    if (!m_ToolBar.CreateEx(this, TBSTYLE_FLAT, TOOLBAR_STYLE) || !m_ToolBar.LoadToolBar(ID_TOOLBAR)) {
        MYTRACE("CToolBar::CreateEx: failed");
        return FALSE;
    }

    // 为 ToolBar 加载 24bit 位图
    CBitmap bmp;
    BITMAP bm;
    CImageList imgList;
    bmp.LoadBitmap(ID_TOOLBAR);
    bmp.GetBitmap(&bm);
    imgList.Create(bm.bmHeight, bm.bmHeight, ILC_COLOR24 | ILC_MASK, bm.bmWidth / bm.bmHeight, 0);
    imgList.Add(&bmp, RGB(255, 0, 255));
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
    if (fileDlg.DoModal() == IDOK) {
        CString str = _T("full path: ") + fileDlg.GetPathName();
        MessageBox(str, _T("info"), MB_ICONINFORMATION | MB_OK);
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
