// FontSheet.cpp : implementation file
//

#include "StdAfx.h"
#include "RichEdit1.h"
#include "FontPage.h"
#include "EffectPage.h"
#include "ColorPage.h"
#include "FontSizePage.h"
#include "FontSheet.h"


// CFontSheet

IMPLEMENT_DYNAMIC(CFontSheet, CPropertySheet)

CFontSheet::CFontSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
    :CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CFontSheet::CFontSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
    :CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
    AddPage(&m_FontPage);
    AddPage(&m_EffectPage);
    AddPage(&m_ColorPage);
    AddPage(&m_FontSizePage);
}

CFontSheet::~CFontSheet()
{
}


BEGIN_MESSAGE_MAP(CFontSheet, CPropertySheet)
END_MESSAGE_MAP()


// CFontSheet message handlers
