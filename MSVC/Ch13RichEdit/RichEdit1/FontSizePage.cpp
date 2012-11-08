// FontSizePage.cpp : implementation file
//

#include "StdAfx.h"
#include "RichEdit1.h"
#include "FontSizePage.h"


// CFontSizePage dialog

IMPLEMENT_DYNAMIC(CFontSizePage, CPropertyPage)

CFontSizePage::CFontSizePage()
    : CPropertyPage(CFontSizePage::IDD)
    , m_FontSize(12)
{
}

CFontSizePage::~CFontSizePage()
{
}

void CFontSizePage::DoDataExchange(CDataExchange* pDX)
{
    MYTRACE("SaveAndValidate = %d", pDX->m_bSaveAndValidate);
    CPropertyPage::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_FONTSIZE, m_FontSize);
    DDV_MinMaxInt(pDX, m_FontSize, 8, 24);
}


BEGIN_MESSAGE_MAP(CFontSizePage, CPropertyPage)
END_MESSAGE_MAP()


// CFontSizePage message handlers

BOOL CFontSizePage::OnCommand(WPARAM wParam, LPARAM lParam)
{
    SetModified(TRUE);
    return CPropertyPage::OnCommand(wParam, lParam);
}

BOOL CFontSizePage::OnInitDialog()
{
    CPropertyPage::OnInitDialog();
    ((CSpinButtonCtrl*) GetDlgItem(IDC_SPIN1))->SetRange(8, 24);
    return TRUE;    // return TRUE unless you set the focus to a control, EXCEPTION: OCX Property Pages should return FALSE
}
