// ProgressDlg.cpp
//

#include "StdAfx.h"
#include "ProgBarEvent.h"
#include "ProgressDlg.h"

// CProgressDlg dialog

int CProgressDlg::Count = 0;

CEvent CProgressDlg::EventStart;
CEvent CProgressDlg::EventCancel;

IMPLEMENT_DYNAMIC(CProgressDlg, CDialog)

CProgressDlg::CProgressDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CProgressDlg::IDD, pParent), m_Timer(0)
{
}

CProgressDlg::~CProgressDlg()
{
}

void CProgressDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}

// 进度条计算线程
UINT CProgressDlg::ProgressThread(LPVOID param)
{
    ::WaitForSingleObject(EventStart, INFINITE);
    TRACE_ERR("progress thread start.");

    Count = 0;
    while (Count < MAX_COUNT) {
        Sleep(10);
        ::InterlockedIncrement((long*) &Count);

        // 每循环空当检测 EventCancel 事件
        if (::WaitForSingleObject(EventCancel, 0) == WAIT_OBJECT_0)
            break;
    }

    // 投递消息通知主线程: 计算线程已经结束
    ::PostMessage((HWND) param, WM_THREADFINISHED, 0, 0);
    Count = 0;
    return 0;
}

BEGIN_MESSAGE_MAP(CProgressDlg, CDialog)
    ON_BN_CLICKED(ID_START, &CProgressDlg::OnBnClickedStart)
    ON_BN_CLICKED(IDCANCEL, &CProgressDlg::OnBnClickedCancel)
    ON_WM_TIMER()
    ON_MESSAGE(WM_THREADFINISHED, OnThreadFinished)
END_MESSAGE_MAP()


// CProgressDlg message handlers

void CProgressDlg::OnBnClickedStart()
{
    const UINT_PTR TIMER_ID = 1;
    m_Timer = SetTimer(TIMER_ID, 10, NULL);     // elapse = 10 ms
    ASSERT(m_Timer != 0);
    GetDlgItem(ID_START)->EnableWindow(FALSE);  // 禁用按钮, 防止重入 OnBnClickedStart
    EventStart.SetEvent();
}

void CProgressDlg::OnBnClickedCancel()
{
    if (Count == 0)
        EventStart.SetEvent();  // 未开始时, 先将 EventStart 激活
    EventCancel.SetEvent();
}

void CProgressDlg::OnTimer(UINT_PTR nIDEvent)
{
    CProgressCtrl* prog = (CProgressCtrl*) GetDlgItem(IDC_PROGRESS1);
    // *100 即让其取值在 0~100, 默认 rang 在 0~100, 可用 CProgressCtrl::SetRange 设置
    prog->SetPos(Count * 100 / MAX_COUNT);
}

LRESULT CProgressDlg::OnThreadFinished(WPARAM wparam, LPARAM lparam)
{
    CDialog::OnOK();
    return 0;
}

BOOL CProgressDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
    AfxBeginThread(ProgressThread, (LPVOID) GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
    return TRUE;  // return TRUE unless you set the focus to a control, EXCEPTION: OCX Property Pages should return FALSE
}
