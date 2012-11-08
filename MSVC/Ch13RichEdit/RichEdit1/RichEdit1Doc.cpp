// RichEdit1Doc.cpp : implementation of the CRichEdit1Doc class
//

#include "StdAfx.h"
#include "RichEdit1.h"

#include "RichEdit1Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRichEdit1Doc

IMPLEMENT_DYNCREATE(CRichEdit1Doc, CDocument)

BEGIN_MESSAGE_MAP(CRichEdit1Doc, CDocument)
END_MESSAGE_MAP()


const _TCHAR* CRichEdit1Doc::DEF_INIT_TEXT = _T("Hello World!");


CRichEdit1Doc::CRichEdit1Doc()
{
}

CRichEdit1Doc::~CRichEdit1Doc()
{
}

BOOL CRichEdit1Doc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;
    m_Text = DEF_INIT_TEXT;
    return TRUE;
}

// CRichEdit1Doc serialization

void CRichEdit1Doc::Serialize(CArchive& ar)
{
    if (ar.IsStoring()) {
        // TODO: add storing code here
    }
    else {
        // TODO: add loading code here
    }
}


// CRichEdit1Doc diagnostics

#ifdef _DEBUG
void CRichEdit1Doc::AssertValid() const
{
    CDocument::AssertValid();
}

void CRichEdit1Doc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG


// CRichEdit1Doc commands
