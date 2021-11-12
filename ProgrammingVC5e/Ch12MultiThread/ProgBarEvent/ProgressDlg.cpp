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

// �����������߳�
UINT CProgressDlg::ProgressThread(LPVOID param)
{
    ::WaitForSingleObject(EventStart, INFINITE);
    TRACE_ERR("progress thread start.");

    Count = 0;
    while (Count < MAX_COUNT) {
        Sleep(10);
        ::InterlockedIncrement((long*) &Count);

        // ÿѭ���յ���� EventCancel �¼�
        if (::WaitForSingleObject(EventCancel, 0) == WAIT_OBJECT_0)
            break;
    }

    // Ͷ����Ϣ֪ͨ���߳�: �����߳��Ѿ�����
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
    GetDlgItem(ID_START)->EnableWindow(FALSE);  // ���ð�ť, ��ֹ���� OnBnClickedStart
    EventStart.SetEvent();
}

void CProgressDlg::OnBnClickedCancel()
{
    if (Count == 0)
        EventStart.SetEvent();  // δ��ʼʱ, �Ƚ� EventStart ����
    EventCancel.SetEvent();
}

void CProgressDlg::OnTimer(UINT_PTR nIDEvent)
{
    CProgressCtrl* prog = (CProgressCtrl*) GetDlgItem(IDC_PROGRESS1);
    // *100 ������ȡֵ�� 0~100, Ĭ�� rang �� 0~100, ���� CProgressCtrl::SetRange ����
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
