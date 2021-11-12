// DBufScrollDoc.cpp : implementation of the CDBufScrollDoc class
//

#include "StdAfx.h"
#include "DBufScroll.h"

#include "DBufScrollDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDBufScrollDoc

IMPLEMENT_DYNCREATE(CDBufScrollDoc, CDocument)

BEGIN_MESSAGE_MAP(CDBufScrollDoc, CDocument)
END_MESSAGE_MAP()


// CDBufScrollDoc construction/destruction

CDBufScrollDoc::CDBufScrollDoc()
{
    // TODO: add one-time construction code here
}

CDBufScrollDoc::~CDBufScrollDoc()
{
}

BOOL CDBufScrollDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;

    // TODO: add reinitialization code here
    // (SDI documents will reuse this document)

    return TRUE;
}

// CDBufScrollDoc serialization

void CDBufScrollDoc::Serialize(CArchive& ar)
{
    if (ar.IsStoring()) {
        // TODO: add storing code here
    }
    else {
        // TODO: add loading code here
    }
}


// CDBufScrollDoc diagnostics

#ifdef _DEBUG
void CDBufScrollDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CDBufScrollDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG
