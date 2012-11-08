// IEBrowserDoc.cpp : implementation of the CIEBrowserDoc class
//

#include "StdAfx.h"
#include "IEBrowser.h"

#include "IEBrowserDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIEBrowserDoc

IMPLEMENT_DYNCREATE(CIEBrowserDoc, CDocument)

BEGIN_MESSAGE_MAP(CIEBrowserDoc, CDocument)
END_MESSAGE_MAP()


// CIEBrowserDoc construction/destruction

CIEBrowserDoc::CIEBrowserDoc()
{
    // TODO: add one-time construction code here

}

CIEBrowserDoc::~CIEBrowserDoc()
{
}

BOOL CIEBrowserDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;

    // TODO: add reinitialization code here
    // (SDI documents will reuse this document)

    return TRUE;
}




// CIEBrowserDoc serialization

void CIEBrowserDoc::Serialize(CArchive& ar)
{
    if (ar.IsStoring()) {
        // TODO: add storing code here
    }
    else {
        // TODO: add loading code here
    }
}


// CIEBrowserDoc diagnostics

#ifdef _DEBUG
void CIEBrowserDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CIEBrowserDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG


// CIEBrowserDoc commands
