// MyDialog1.cpp : implementation file
//

#include "StdAfx.h"
#include "SubCtrl.h"
#include "MyDialog1.h"


// CMyDialog1 dialog

IMPLEMENT_DYNAMIC(CMyDialog1, CDialog)

CMyDialog1::CMyDialog1(CWnd* pParent /*=NULL*/)
    : CDialog(CMyDialog1::IDD, pParent)
{
}

CMyDialog1::~CMyDialog1()
{
}

void CMyDialog1::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyDialog1, CDialog)
END_MESSAGE_MAP()


// CMyDialog1 message handlers

BOOL CMyDialog1::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_NonNumEdit.SubclassDlgItem(IDC_EDIT1, this);
    m_UpperEdit.SubclassDlgItem(IDC_EDIT2, this);

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}
