// RygDlg.cpp : implementation file
//

#include "StdAfx.h"
#include "PersistWnd.h"
#include "RygDlg.h"

// CRygDlg dialog

IMPLEMENT_DYNAMIC(CRygDlg, CDialog)

CRygDlg::CRygDlg(CWnd* pParent /*=NULL*/) :
    CDialog(CRygDlg::IDD, pParent),
    m_RygState(RYG_OFF)
{
    LoadRyg();
}

CRygDlg::~CRygDlg()
{
}

void CRygDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRygDlg, CDialog)
    ON_CONTROL(0, IDC_RYG, CRygDlg::OnClickedRyg)
END_MESSAGE_MAP()


// CRygDlg message handlers

void CRygDlg::OnClickedRyg()
{
    switch(m_RygState) {
    case RYG_OFF:
        m_RygState = RYG_RED;
        break;
    case RYG_RED:
        m_RygState = RYG_YELLOW;
        break;
    case RYG_YELLOW:
        m_RygState = RYG_GREEN;
        break;
    case RYG_GREEN:
        m_RygState = RYG_OFF;
        break;
    }
    GetDlgItem(IDC_RYG)->SendMessage(WM_RYG_SETSTATE, m_RygState);
}
