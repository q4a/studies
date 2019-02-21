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
    GetDlgItem(ID_START)->EnableWindow(FALSE);  // 禁用按钮, 防止重入 OnBnClickedStart

    MSG msg;
    for (m_Count = 0; m_Count < MAX_COUNT; ++m_Count) {
        Sleep(1);

        // 内嵌消息循环, 下面是 if 而不是 while, 即在计算间隔只尝试抽取一个消息
        if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);    // 可引发 WM_TIMER 和其它消息的处理, 不会重入 OnBnClickedStart, 因为按钮已禁用
        }

        // NOTE: m_Count == -1 判断不应放在 for 循环表达式里, 因为 OnBnClickedCancel 是在 DispatchMessage 中处理的, ++m_Count 会改变其值
        if (m_Count == -1)
            break;
    }

    // NOTE: 需要最后完成时, 填满进度条, OnTimer 中的过程可能因为浮点误差无法填满
    CProgressCtrl* prog = (CProgressCtrl*) GetDlgItem(IDC_PROGRESS1);
    if (m_Count == MAX_COUNT)   // 如果不是被取消的
        prog->SetPos(100);

    GetDlgItem(ID_START)->EnableWindow(TRUE);
    KillTimer(m_Timer);
    m_Timer = 0;
    m_Count = 0;
}

void CProgressDlg::OnTimer(UINT_PTR nIDEvent)
{
    CProgressCtrl* prog = (CProgressCtrl*) GetDlgItem(IDC_PROGRESS1);
    // *100 即让其取值在 0~100, 默认 rang 在 0~100, 可用 CProgressCtrl::SetRange 设置
    prog->SetPos(m_Count * 100 / MAX_COUNT);
}

void CProgressDlg::OnBnClickedCancel()
{
    if (m_Count == 0)
        CDialog::OnCancel();    // 如果还没开始, 则退出对话框
    else
        m_Count = -1;           // m_Count = -1 表示被取消
}
