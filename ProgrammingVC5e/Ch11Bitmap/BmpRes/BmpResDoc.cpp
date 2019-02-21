// BmpResDoc.cpp : implementation of the CBmpResDoc class
//

#include "StdAfx.h"
#include "BmpRes.h"

#include "BmpResDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CBmpResDoc

IMPLEMENT_DYNCREATE(CBmpResDoc, CDocument)

BEGIN_MESSAGE_MAP(CBmpResDoc, CDocument)
END_MESSAGE_MAP()


// CBmpResDoc construction/destruction

CBmpResDoc::CBmpResDoc()
{
}

CBmpResDoc::~CBmpResDoc()
{
}

BOOL CBmpResDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;

    // TODO: add reinitialization code here
    // (SDI documents will reuse this document)

    return TRUE;
}

// CBmpResDoc serialization

void CBmpResDoc::Serialize(CArchive& ar)
{
    if (ar.IsStoring()) {
        // TODO: add storing code here
    }
    else {
        // TODO: add loading code here
    }
}


// CBmpResDoc diagnostics

#ifdef _DEBUG
void CBmpResDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CBmpResDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG


// CBmpResDoc commands
