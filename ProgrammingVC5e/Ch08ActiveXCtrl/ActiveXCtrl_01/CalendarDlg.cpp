// CalendarDlg.cpp : implementation file
//

#include "StdAfx.h"
#include "ActiveXCtrl_01.h"
#include "Calendar.h"
#include "CalendarDlg.h"


// CCalendarDlg dialog

IMPLEMENT_DYNAMIC(CCalendarDlg, CDialog)

CCalendarDlg::CCalendarDlg(CWnd* pParent /*=NULL*/) :
    CDialog(CCalendarDlg::IDD, pParent),
    m_nDay(0), m_nMonth(0), m_nYear(0),
    m_BackColor(RGB(0xFF, 0xCC, 0xFF))  // ��ɫ
{
}

CCalendarDlg::~CCalendarDlg()
{
}

void CCalendarDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_DAY, m_nDay);
    DDX_Text(pDX, IDC_EDIT_MONTH, m_nMonth);
    DDX_Text(pDX, IDC_EDIT_YEAR, m_nYear);
    DDX_Control(pDX, IDC_CALENDAR1, m_ctrlCalendar);

    // �� Add member variable Wizard �в���ʶ�� Calender �ؼ� (IDC_CALENDAR1)
    // �� Color ����ӳ�䣬��������ӳ����Ҫ�ֹ����
    DDX_OCColor(pDX, IDC_CALENDAR1, DISPID_BACKCOLOR, (OLE_COLOR) m_BackColor);
}

// �ؼ���Ϣӳ��
BEGIN_MESSAGE_MAP(CCalendarDlg, CDialog)
    ON_BN_CLICKED(IDC_BUTTON_SELECTDATE, &CCalendarDlg::OnBnClickedButtonSelectdate)
    ON_BN_CLICKED(IDC_BUTTON_NEXTWEEK, &CCalendarDlg::OnBnClickedButtonNextweek)
END_MESSAGE_MAP()

// ActiveX �ؼ�����Ϣӳ��
BEGIN_EVENTSINK_MAP(CCalendarDlg, CDialog)
// 3 �� NewMonth �¼��� ID
ON_EVENT(CCalendarDlg, IDC_CALENDAR1, 3, CCalendarDlg::OnNewMonthCalendar1, VTS_NONE)
END_EVENTSINK_MAP()

// CCalendarDlg message handlers

BOOL CCalendarDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // ��Ϊ�������� VARIANT û�ж�Ӧ��ӳ�� DDX ���������Ա������ ActiveX ��װ��
    // �ķ�������ʼ���ؼ�����

    m_ctrlCalendar.put_Value(m_vValue);

    // �� ActiveX �ؼ��������ڴ���
    // ���û��������ؼ��ĸ������˳���ActiveX �ؼ��ʹӽ��̿ռ���ж�ص�
    // ���������ֱ�������˳�������� AfxOleUnlockControl() ��ж��
    // �����ԣ�����һ�� ActiveX �� dll �ڿؼ����ڴ�ʱ���أ�����һ��һֱ�����ڴ�ռ��У���
    // ���ڴ��ڹر�ʱж�أ��������� AfxOleLockControl() ��������
    AfxOleLockControl(m_ctrlCalendar.GetClsid());

    // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
    return TRUE;
}

void CCalendarDlg::OnNewMonthCalendar1()
{
    AfxMessageBox(_T("Event: Calendar: NewMonth"));
}

void CCalendarDlg::OnBnClickedButtonSelectdate()
{
    // ���ﲻʹ�� UpdateData(FALSE)����Ϊ UpdateData() �ᴥ�� DoDataExchange()��
    // �����ᴫ�����еĿؼ����ݵ�ӳ������У����������� m_ctrlCalendar ��������������

    // ��������ã����ֹ��� DDX + ���ÿؼ���װ�෽�������ֶ�

    CDataExchange dx(this, TRUE);
    DDX_Text(&dx, IDC_EDIT_DAY, m_nDay);
    DDX_Text(&dx, IDC_EDIT_MONTH, m_nMonth);
    DDX_Text(&dx, IDC_EDIT_YEAR, m_nYear);

    m_ctrlCalendar.put_Day(m_nDay);
    m_ctrlCalendar.put_Month(m_nMonth);
    m_ctrlCalendar.put_Year(m_nYear);
}

void CCalendarDlg::OnBnClickedButtonNextweek()
{
    m_ctrlCalendar.NextWeek();
}

void CCalendarDlg::OnOK()
{
    CDialog::OnOK();

    // ������Ϊ�������� VARIANT û�ж�Ӧ��ӳ�� DDX ���������Ա������ ActiveX ��װ��
    // �ķ�����ȡ�ؿؼ����ݣ�����Ի������
    m_vValue = m_ctrlCalendar.get_Value();
}
