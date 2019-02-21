////////////////////////////////////////////////////////////////////////////////
// 文    件 : MainFrame.h
// 功能说明 :
//   主框架窗口
//
// 版    本 : 1.0
// 作    者 : Breaker Zhao <breaker.zy_AT_gmail>
// 日    期 : 2010-10
////////////////////////////////////////////////////////////////////////////////

#ifndef __MAINFRAME_H__
#define __MAINFRAME_H__

////////////////////////////////////////////////////////////////////////////////
// 主框架窗口类 CMainFrame
////////////////////////////////////////////////////////////////////////////////

class CMainFrame : public CFrameWnd {
    DECLARE_DYNAMIC(CMainFrame) // MFC RTTI 支持

public:
    CMainFrame() {}
    virtual ~CMainFrame() {}

public:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

#ifdef _DEBUG
    // 用于 Debug 版的诊断函数
    virtual void AssertValid() const {
        CFrameWnd::AssertValid();
    }
    virtual void Dump(CDumpContext& dc) const {
        CFrameWnd::Dump(dc);
    }
#endif  // _DEBUG

private:
    // 消息处理

    afx_msg int OnCreate(LPCREATESTRUCT cs);
    afx_msg void OnFileOpen();
    afx_msg void OnAppAbout();
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    afx_msg void OnDataRace1();
    afx_msg void OnDataRace2();
    afx_msg void OnDataRace3();

    DECLARE_MESSAGE_MAP()

private:
    BOOL CreateToolBar();
    BOOL CreateClientView();
    BOOL CreateStatusBar();

    void TestDataRace(AFX_THREADPROC threadProc);

private:
    static UINT StatusBarInd[]; // 状态栏指示器 (indicator)

    CToolBar    m_ToolBar;      // 工具栏对象
    CStatusBar  m_StatusBar;    // 状态栏对象
    CClientView m_ClientView;   // 客户区窗口, 占据除 ToolBar, StatusBar 之外的窗口客户区
};

////////////////////////////////////////////////////////////////////////////////
// 关于对话框类 CAboutDlg
////////////////////////////////////////////////////////////////////////////////

class CAboutDlg : public CDialog {
public:
    enum { IDD = IDD_ABOUTBOX };

public:
    CAboutDlg() : CDialog(CAboutDlg::IDD) {}

private:
    // DDX/DDV
    virtual void DoDataExchange(CDataExchange* pDX) {
        CDialog::DoDataExchange(pDX);
    }

    // 消息处理
    DECLARE_MESSAGE_MAP()
};

#endif  // __MAINFRAME_H__
