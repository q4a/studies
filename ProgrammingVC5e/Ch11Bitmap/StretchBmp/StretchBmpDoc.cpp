// StretchBmpDoc.cpp : implementation of the CStretchBmpDoc class
//

#include "StdAfx.h"
#include "StretchBmp.h"

#include "StretchBmpDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStretchBmpDoc

IMPLEMENT_DYNCREATE(CStretchBmpDoc, CDocument)

BEGIN_MESSAGE_MAP(CStretchBmpDoc, CDocument)
END_MESSAGE_MAP()


// CStretchBmpDoc construction/destruction

CStretchBmpDoc::CStretchBmpDoc()
{
    // TODO: add one-time construction code here

}

CStretchBmpDoc::~CStretchBmpDoc()
{
}

BOOL CStretchBmpDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;

    // TODO: add reinitialization code here
    // (SDI documents will reuse this document)

    return TRUE;
}

// CStretchBmpDoc serialization

void CStretchBmpDoc::Serialize(CArchive& ar)
{
    if (ar.IsStoring()) {
        // TODO: add storing code here
    }
    else {
        // TODO: add loading code here
    }
}


// CStretchBmpDoc diagnostics

#ifdef _DEBUG
void CStretchBmpDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CStretchBmpDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG
