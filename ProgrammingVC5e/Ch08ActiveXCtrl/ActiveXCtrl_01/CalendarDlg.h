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

// �ؼ�ӳ�����
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

public:
    short m_nDay;
    short m_nMonth;
    short m_nYear;
    CCalendar m_ctrlCalendar;

    // Ŀǰ Win32/MFC �� COLORREF �� COM/ActiveX �� OLE_COLOR ��ʵ����һ���ģ����� 32bit ����
    ULONG m_BackColor;

// ���ػ����Ա����
public:
    virtual BOOL OnInitDialog();
protected:
    virtual void OnOK();

// ��Ϣӳ��ʹ�����
public:
    DECLARE_MESSAGE_MAP()

    afx_msg void OnBnClickedButtonSelectdate();
    afx_msg void OnBnClickedButtonNextweek();

// ActiveX �ؼ���Ϣӳ��ʹ�����
public:
    DECLARE_EVENTSINK_MAP()

    void OnNewMonthCalendar1();
};
