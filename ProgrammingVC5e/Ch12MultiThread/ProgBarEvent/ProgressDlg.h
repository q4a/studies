#pragma once


// CProgressDlg dialog

class CProgressDlg : public CDialog {
    DECLARE_DYNAMIC(CProgressDlg)

public:
    CProgressDlg(CWnd* pParent = NULL);   // standard constructor
    virtual ~CProgressDlg();

// Dialog Data
    enum { IDD = IDD_PROGRESS };
    enum { WM_THREADFINISHED = WM_USER + 1 };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();

private:
    afx_msg void OnBnClickedStart();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnBnClickedCancel();
    afx_msg LRESULT OnThreadFinished(WPARAM wparam, LPARAM lparam);
    DECLARE_MESSAGE_MAP()

private:
    static UINT ProgressThread(LPVOID param);

private:
    UINT_PTR    m_Timer;    // Timer ID

    static int          Count;
    static const int    MAX_COUNT = 100;
    static CEvent       EventStart;
    static CEvent       EventCancel;
};
