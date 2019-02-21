// ActiveXCtrlDlg.h : header file
//

#pragma once


// CActiveXCtrlDlg dialog
class CActiveXCtrlDlg : public CDialog {
// Construction
public:
    CActiveXCtrlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
    enum { IDD = IDD_ACTIVEXCTRL_01_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
    HICON m_hIcon;

// 重载基类成员函数
protected:
    virtual BOOL OnInitDialog();

// 消息映射和处理函数
protected:

    DECLARE_MESSAGE_MAP()

    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();

public:
    afx_msg void OnBnClickedButtonOpencalendar();
};
