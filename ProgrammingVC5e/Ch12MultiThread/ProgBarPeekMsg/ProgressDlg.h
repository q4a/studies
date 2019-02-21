#pragma once


// CProgressDlg dialog

class CProgressDlg : public CDialog {
    DECLARE_DYNAMIC(CProgressDlg)

public:
    CProgressDlg(CWnd* pParent = NULL);   // standard constructor
    virtual ~CProgressDlg();

// Dialog Data
    enum { IDD = IDD_PROGRESS };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

private:
    afx_msg void OnBnClickedStart();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnBnClickedCancel();
    DECLARE_MESSAGE_MAP()

private:
    UINT_PTR    m_Timer;    // Timer ID
    int         m_Count;

    static const int    MAX_COUNT = 100;
};
