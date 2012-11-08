#pragma once
#include "calendar.h"


// CCalendarDlg dialog

class CCalendarDlg : public CDialog {
    DECLARE_DYNAMIC(CCalendarDlg)

public:
    CCalendarDlg(CWnd* pParent = NULL);   // standard constructor
    virtual ~CCalendarDlg();

// Dialog Data
    enum { IDD = IDD_CALENDARDLG };

public:
    COleVariant m_vValue;

// 控件映射变量
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

public:
    short m_nDay;
    short m_nMonth;
    short m_nYear;
    CCalendar m_ctrlCalendar;

    // 目前 Win32/MFC 的 COLORREF 和 COM/ActiveX 的 OLE_COLOR 的实质是一样的，都是 32bit 整型
    ULONG m_BackColor;

// 重载基类成员函数
public:
    virtual BOOL OnInitDialog();
protected:
    virtual void OnOK();

// 消息映射和处理函数
public:
    DECLARE_MESSAGE_MAP()

    afx_msg void OnBnClickedButtonSelectdate();
    afx_msg void OnBnClickedButtonNextweek();

// ActiveX 控件消息映射和处理函数
public:
    DECLARE_EVENTSINK_MAP()

    void OnNewMonthCalendar1();
};
