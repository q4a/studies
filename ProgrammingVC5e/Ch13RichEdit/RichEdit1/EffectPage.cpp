// EffectPage.cpp : implementation file
//

#include "StdAfx.h"
#include "RichEdit1.h"
#include "EffectPage.h"


// CEffectPage dialog

IMPLEMENT_DYNAMIC(CEffectPage, CPropertyPage)

CEffectPage::CEffectPage()
    : CPropertyPage(CEffectPage::IDD)
    , m_Bold(FALSE), m_Italic(FALSE), m_Underline(FALSE)
{
}

CEffectPage::~CEffectPage()
{
}

void CEffectPage::DoDataExchange(CDataExchange* pDX)
{
    MYTRACE("SaveAndValidate = %d", pDX->m_bSaveAndValidate);
    CPropertyPage::DoDataExchange(pDX);
    DDX_Check(pDX, IDC_BOLD, m_Bold);
    DDX_Check(pDX, IDC_ITALIC, m_Italic);
    DDX_Check(pDX, IDC_UNDERLINE, m_Underline);
}


BEGIN_MESSAGE_MAP(CEffectPage, CPropertyPage)
END_MESSAGE_MAP()


// CEffectPage message handlers

BOOL CEffectPage::OnCommand(WPARAM wParam, LPARAM lParam)
{
    SetModified(TRUE);
    return CPropertyPage::OnCommand(wParam, lParam);
}
