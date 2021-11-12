////////////////////////////////////////////////////////////////////////////////
// ��    �� : MainFrame.cpp
// ����˵�� :
//   ����ܴ���
//
// ��    �� : 1.0
// ��    �� : Breaker Zhao <breaker.zy_AT_gmail>
// ��    �� : 2010-10
////////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "DataRace.h"
#include "ClientView.h"
#include "MainFrame.h"

////////////////////////////////////////////////////////////////////////////////
// ȫ����
////////////////////////////////////////////////////////////////////////////////

int                 Count1;
CCriticalSection    CSec;

////////////////////////////////////////////////////////////////////////////////
// �����߳�����
////////////////////////////////////////////////////////////////////////////////

UINT WorkThread1(LPVOID param)
{
    int round = (int) (intptr_t) param;
    for (int i = 0; i < round; ++i)
        ++Count1;
    return 0;
}

UINT WorkThread2(LPVOID param)
{
    int round = (int) (intptr_t) param;
    for (int i = 0; i < round; ++i)
        ::InterlockedIncrement((long*) &Count1);
    return 0;
}

UINT WorkThread3(LPVOID param)
{
    int round = (int) (intptr_t) param;
    for (int i = 0; i < round; ++i) {
        CSec.Lock();
        ++Count1;
        CSec.Unlock();
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
// ����ܴ����� CMainFrame
////////////////////////////////////////////////////////////////////////////////

// MFC RTTI ֧��
IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

// ��Ϣӳ��
BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
    ON_WM_CREATE()
    ON_WM_SETFOCUS()
    ON_COMMAND(ID_FILE_OPEN, &CMainFrame::OnFileOpen)
    ON_COMMAND(ID_APP_ABOUT, &CMainFrame::OnAppAbout)
    ON_COMMAND(ID_DATARACE1, &CMainFrame::OnDataRace1)
    ON_COMMAND(ID_DATARACE2, &CMainFrame::OnDataRace2)
    ON_COMMAND(ID_DATARACE3, &CMainFrame::OnDataRace3)
END_MESSAGE_MAP()

// ״̬��ָʾ�� (indicator)
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

    cs.dwExStyle &= ~WS_EX_CLIENTEDGE;  // ȥ���³��߿���ʽ (sunken edge)

    // ���ô�����Ļ����
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
        TRACE_ERR("failed to create status bar");
        return FALSE;
    }
    return TRUE;
}

BOOL CMainFrame::CreateClientView()
{
    // NOTE: AFX_WS_DEFAULT_VIEW Ϊ��ͼ���ڵ�ͨ����ʽ
    if (!m_ClientView.Create(0, 0, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, 0)) {
        TRACE_ERR("failed to create client view");
        return FALSE;
    }
    return TRUE;
}

BOOL CMainFrame::CreateToolBar()
{
    const DWORD TOOLBAR_STYLE = WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC;

    // NOTE: LoadToolBar ֻ�ܼ��� 16 ɫ (���� 256 ɫ) λͼ, ������� 8bit ����λͼ������ʾ����
    if (!m_ToolBar.CreateEx(this, TBSTYLE_FLAT, TOOLBAR_STYLE) || !m_ToolBar.LoadToolBar(ID_TOOLBAR)) {
        TRACE_ERR("CToolBar::CreateEx: failed");
        return FALSE;
    }

    // Ϊ ToolBar ���� 24bit λͼ
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

    // ʹ ToolBar ��Ϊ��ͣ����
    m_ToolBar.EnableDocking(CBRS_ALIGN_ANY);
    EnableDocking(CBRS_ALIGN_ANY);
    DockControlBar(&m_ToolBar);
    return TRUE;
}

void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
    // ת�� WM_SETFOCUS ��Ϣ�� ClientView
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
    // ί�� ClientView �� WM_COMMAND ��Ϣ�Ĵ���
    if (m_ClientView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
        return TRUE;
    // ClientView ���� FALSE ʱ, ����Ĭ�ϴ���
    return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CMainFrame::TestDataRace(AFX_THREADPROC threadProc)
{
    ASSERT(threadProc != NULL);

    Count1 = 0;
    const int PART1 = 10000;
    const int PART2 = 10000;
    CWinThread* pThread1 = AfxBeginThread(threadProc, (void*) (intptr_t) PART1, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
    CWinThread* pThread2 = AfxBeginThread(threadProc, (void*) (intptr_t) PART2, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);

    HANDLE hThreads[2] = {pThread1->m_hThread, pThread2->m_hThread};
    pThread1->ResumeThread();
    pThread2->ResumeThread();

    if (::WaitForMultipleObjects(_countof(hThreads), hThreads, TRUE, INFINITE) != WAIT_OBJECT_0) {
        TRACE_FAIL("WaitForMultipleObjects", ::GetLastError());
        return;
    }

    CClientDC dc(&m_ClientView);
    CString str;
    str.Format(_T("global count is: %d."), Count1);
    if (Count1 != PART1 + PART2)
        str.Append(_T(" data race occurred."));
    else
        str.Append(_T(" data race NOT occurred."));

    m_ClientView.SetShowText(str);
    m_ClientView.Invalidate();
    m_ClientView.UpdateWindow();
}

void CMainFrame::OnDataRace1()
{
    TestDataRace(WorkThread1);
}

void CMainFrame::OnDataRace2()
{
    TestDataRace(WorkThread2);
}

void CMainFrame::OnDataRace3()
{
    TestDataRace(WorkThread3);
}

////////////////////////////////////////////////////////////////////////////////
// ���ڶԻ����� CAboutDlg
////////////////////////////////////////////////////////////////////////////////

// ��Ϣӳ��
BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()
