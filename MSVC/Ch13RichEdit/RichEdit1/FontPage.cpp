// FontPage.cpp : implementation file
//

#include "StdAfx.h"
#include "RichEdit1.h"
#include "FontPage.h"

// CFontPage dialog

LPCTSTR CFontPage::FontTable[] = {
    _T("Times New Roman"), _T("Arial"), _T("Courier New")
};

IMPLEMENT_DYNAMIC(CFontPage, CPropertyPage)

CFontPage::CFontPage()
    : CPropertyPage(CFontPage::IDD)
    , m_Font(0)
{
}

CFontPage::~CFontPage()
{
}

void CFontPage::DoDataExchange(CDataExchange* pDX)
{
    MYTRACE("SaveAndValidate = %d", pDX->m_bSaveAndValidate);
    CPropertyPage::DoDataExchange(pDX);
    DDX_Radio(pDX, IDC_FONT, m_Font);
}


BEGIN_MESSAGE_MAP(CFontPage, CPropertyPage)
END_MESSAGE_MAP()


// CFontPage message handlers

BOOL CFontPage::OnApply()
{
    MYTRACE("enter");
    CView* view = ((CFrameWnd*) AfxGetMainWnd())->GetActiveView();
    view->SendMessage(WM_USERAPPLY);
    return TRUE;
}

BOOL CFontPage::OnCommand(WPARAM wParam, LPARAM lParam)
{
    SetModified(TRUE);
    return CPropertyPage::OnCommand(wParam, lParam);
}

LPCTSTR CFontPage::GetFont()
{
    if (m_Font < 0 || m_Font >= _countof(FontTable))
        m_Font = 0;
    return FontTable[m_Font];
}
