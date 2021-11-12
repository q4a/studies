// ProgressDlg.cpp
//

#include "StdAfx.h"
#include "ProgBarPeekMsg.h"
#include "ProgressDlg.h"


// CProgressDlg dialog

IMPLEMENT_DYNAMIC(CProgressDlg, CDialog)

CProgressDlg::CProgressDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CProgressDlg::IDD, pParent), m_Timer(0), m_Count(0)
{
}

CProgressDlg::~CProgressDlg()
{
}

void CProgressDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CProgressDlg, CDialog)
    ON_BN_CLICKED(ID_START, &CProgressDlg::OnBnClickedStart)
    ON_WM_TIMER()
    ON_BN_CLICKED(IDCANCEL, &CProgressDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CProgressDlg message handlers

void CProgressDlg::OnBnClickedStart()
{
    const UINT_PTR TIMER_ID = 1;
    m_Timer = SetTimer(TIMER_ID, 10, NULL);   // elapse = 10 ms
    ASSERT(m_Timer != 0);
    GetDlgItem(ID_START)->EnableWindow(FALSE);  // ���ð�ť, ��ֹ���� OnBnClickedStart

    MSG msg;
    for (m_Count = 0; m_Count < MAX_COUNT; ++m_Count) {
        Sleep(1);

        // ��Ƕ��Ϣѭ��, ������ if ������ while, ���ڼ�����ֻ���Գ�ȡһ����Ϣ
        if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);    // ������ WM_TIMER ��������Ϣ�Ĵ���, �������� OnBnClickedStart, ��Ϊ��ť�ѽ���
        }

        // NOTE: m_Count == -1 �жϲ�Ӧ���� for ѭ�����ʽ��, ��Ϊ OnBnClickedCancel ���� DispatchMessage �д����, ++m_Count ��ı���ֵ
        if (m_Count == -1)
            break;
    }

    // NOTE: ��Ҫ������ʱ, ����������, OnTimer �еĹ��̿�����Ϊ��������޷�����
    CProgressCtrl* prog = (CProgressCtrl*) GetDlgItem(IDC_PROGRESS1);
    if (m_Count == MAX_COUNT)   // ������Ǳ�ȡ����
        prog->SetPos(100);

    GetDlgItem(ID_START)->EnableWindow(TRUE);
    KillTimer(m_Timer);
    m_Timer = 0;
    m_Count = 0;
}

void CProgressDlg::OnTimer(UINT_PTR nIDEvent)
{
    CProgressCtrl* prog = (CProgressCtrl*) GetDlgItem(IDC_PROGRESS1);
    // *100 ������ȡֵ�� 0~100, Ĭ�� rang �� 0~100, ���� CProgressCtrl::SetRange ����
    prog->SetPos(m_Count * 100 / MAX_COUNT);
}

void CProgressDlg::OnBnClickedCancel()
{
    if (m_Count == 0)
        CDialog::OnCancel();    // �����û��ʼ, ���˳��Ի���
    else
        m_Count = -1;           // m_Count = -1 ��ʾ��ȡ��
}
