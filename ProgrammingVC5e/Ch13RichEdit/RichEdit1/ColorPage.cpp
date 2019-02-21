// ColorPage.cpp : implementation file
//

#include "StdAfx.h"
#include "RichEdit1.h"
#include "ColorPage.h"


// CColorPage dialog

COLORREF CColorPage::ColorTable[] = {
    RGB(0, 0, 0), RGB(255, 0, 0), RGB(0, 255, 0)
};

IMPLEMENT_DYNAMIC(CColorPage, CPropertyPage)

CColorPage::CColorPage()
    : CPropertyPage(CColorPage::IDD)
    , m_Color(0)
{
}

CColorPage::~CColorPage()
{
}

void CColorPage::DoDataExchange(CDataExchange* pDX)
{
    MYTRACE("SaveAndValidate = %d", pDX->m_bSaveAndValidate);
    CPropertyPage::DoDataExchange(pDX);
    DDX_Radio(pDX, IDC_COLOR, m_Color);
}


BEGIN_MESSAGE_MAP(CColorPage, CPropertyPage)
END_MESSAGE_MAP()


// CColorPage message handlers

BOOL CColorPage::OnCommand(WPARAM wParam, LPARAM lParam)
{
    SetModified(TRUE);
    return CPropertyPage::OnCommand(wParam, lParam);
}

COLORREF CColorPage::GetColor()
{
    if (m_Color < 0 || m_Color >= _countof(ColorTable))
        m_Color = 0;
    return ColorTable[m_Color];
}
