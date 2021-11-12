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
    m_BackColor(RGB(0xFF, 0xCC, 0xFF))  // 紫色
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

    // 在 Add member variable Wizard 中不能识别 Calender 控件 (IDC_CALENDAR1)
    // 的 Color 类型映射，所以下面映射需要手工添加
    DDX_OCColor(pDX, IDC_CALENDAR1, DISPID_BACKCOLOR, (OLE_COLOR) m_BackColor);
}

// 控件消息映射
BEGIN_MESSAGE_MAP(CCalendarDlg, CDialog)
    ON_BN_CLICKED(IDC_BUTTON_SELECTDATE, &CCalendarDlg::OnBnClickedButtonSelectdate)
    ON_BN_CLICKED(IDC_BUTTON_NEXTWEEK, &CCalendarDlg::OnBnClickedButtonNextweek)
END_MESSAGE_MAP()

// ActiveX 控件的消息映射
BEGIN_EVENTSINK_MAP(CCalendarDlg, CDialog)
// 3 是 NewMonth 事件的 ID
ON_EVENT(CCalendarDlg, IDC_CALENDAR1, 3, CCalendarDlg::OnNewMonthCalendar1, VTS_NONE)
END_EVENTSINK_MAP()

// CCalendarDlg message handlers

BOOL CCalendarDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // 因为变体类型 VARIANT 没有对应的映射 DDX 函数，所以必须调用 ActiveX 包装类
    // 的方法来初始化控件数据

    m_ctrlCalendar.put_Value(m_vValue);

    // 将 ActiveX 控件锁定在内存中
    // 如果没锁定，则控件的父窗口退出后，ActiveX 控件就从进程空间中卸载掉
    // 如果锁定，直到进程退出，或调用 AfxOleUnlockControl() 才卸载
    // 经测试，总有一份 ActiveX 的 dll 在控件窗口打开时加载（还有一份一直留在内存空间中），
    // 又在窗口关闭时卸载，调不调用 AfxOleLockControl() 都是这样
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
    // 这里不使用 UpdateData(FALSE)，因为 UpdateData() 会触发 DoDataExchange()，
    // 而它会传送所有的控件数据到映射变量中，包括重量的 m_ctrlCalendar 的所有数据属性

    // 而这里采用：“手工的 DDX + 调用控件包装类方法”的手段

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

    // 还是因为变体类型 VARIANT 没有对应的映射 DDX 函数，所以必须调用 ActiveX 包装类
    // 的方法来取回控件数据，放入对话框变量
    m_vValue = m_ctrlCalendar.get_Value();
}
