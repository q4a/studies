#pragma once


// CComputeSqrtDlg dialog

class CComputeSqrtDlg : public CDialog {
    DECLARE_DYNAMIC(CComputeSqrtDlg)

public:
    CComputeSqrtDlg(CWnd* pParent = NULL);   // standard constructor
    virtual ~CComputeSqrtDlg();

// Dialog Data
    enum { IDD = IDD_DIALOG1 };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

public:
    afx_msg void OnBnClickedCompute();
protected:
    DECLARE_MESSAGE_MAP()

public:
    double m_Input;
    double m_Output;
};
