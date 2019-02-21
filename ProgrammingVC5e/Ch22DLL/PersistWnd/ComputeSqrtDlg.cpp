// ComputeSqrtDlg.cpp : implementation file
//

#include "StdAfx.h"
#include "PersistWnd.h"
#include "ComputeSqrtDlg.h"

#include "SquareRoot.h"

// CComputeSqrtDlg dialog

IMPLEMENT_DYNAMIC(CComputeSqrtDlg, CDialog)

CComputeSqrtDlg::CComputeSqrtDlg(CWnd* pParent /*=NULL*/) :
    CDialog(CComputeSqrtDlg::IDD, pParent),
    m_Input(0), m_Output(0)
{
}

CComputeSqrtDlg::~CComputeSqrtDlg()
{
}

void CComputeSqrtDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_INPUT, m_Input);
    DDX_Text(pDX, IDC_OUTPUT, m_Output);
}


BEGIN_MESSAGE_MAP(CComputeSqrtDlg, CDialog)
    ON_BN_CLICKED(IDC_COMPUTE, &CComputeSqrtDlg::OnBnClickedCompute)
END_MESSAGE_MAP()


// CComputeSqrtDlg message handlers

void CComputeSqrtDlg::OnBnClickedCompute()
{
    UpdateData(TRUE);
    m_Output = SquareRoot(m_Input);
    UpdateData(FALSE);
}
