////////////////////////////////////////////////////////////////////////////////
// ��    �� : MainFrame.h
// ����˵�� :
//   ����ܴ���
//
// ��    �� : 1.0
// ��    �� : Breaker Zhao <breaker.zy_AT_gmail>
// ��    �� : 2010-10
////////////////////////////////////////////////////////////////////////////////

#ifndef __MAINFRAME_H__
#define __MAINFRAME_H__

////////////////////////////////////////////////////////////////////////////////
// ����ܴ����� CMainFrame
////////////////////////////////////////////////////////////////////////////////

class CMainFrame : public CFrameWnd {
    DECLARE_DYNAMIC(CMainFrame) // MFC RTTI ֧��

public:
    CMainFrame() {}
    virtual ~CMainFrame() {}

public:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

#ifdef _DEBUG
    // ���� Debug �����Ϻ���
    virtual void AssertValid() const {
        CFrameWnd::AssertValid();
    }
    virtual void Dump(CDumpContext& dc) const {
        CFrameWnd::Dump(dc);
    }
#endif  // _DEBUG

private:
    // ��Ϣ����

    afx_msg int OnCreate(LPCREATESTRUCT cs);
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    afx_msg void OnFileOpen();
    afx_msg void OnAppAbout();
    afx_msg void OnProgress();

    DECLARE_MESSAGE_MAP()

private:
    BOOL CreateToolBar();
    BOOL CreateClientView();
    BOOL CreateStatusBar();

private:
    static UINT StatusBarInd[]; // ״̬��ָʾ�� (indicator)

    CToolBar    m_ToolBar;      // ����������
    CStatusBar  m_StatusBar;    // ״̬������
    CClientView m_ClientView;   // �ͻ�������, ռ�ݳ� ToolBar, StatusBar ֮��Ĵ��ڿͻ���
};

////////////////////////////////////////////////////////////////////////////////
// ���ڶԻ����� CAboutDlg
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

    // ��Ϣ����
    DECLARE_MESSAGE_MAP()
};

#endif  // __MAINFRAME_H__
