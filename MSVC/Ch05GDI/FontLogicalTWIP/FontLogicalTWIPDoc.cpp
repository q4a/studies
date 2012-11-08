// FontLogicalTWIPDoc.cpp : implementation of the CFontLogicalTWIPDoc class
//

#include "StdAfx.h"
#include "FontLogicalTWIP.h"

#include "FontLogicalTWIPDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFontLogicalTWIPDoc

IMPLEMENT_DYNCREATE(CFontLogicalTWIPDoc, CDocument)

BEGIN_MESSAGE_MAP(CFontLogicalTWIPDoc, CDocument)
END_MESSAGE_MAP()


// CFontLogicalTWIPDoc construction/destruction

CFontLogicalTWIPDoc::CFontLogicalTWIPDoc()
{
    // TODO: add one-time construction code here

}

CFontLogicalTWIPDoc::~CFontLogicalTWIPDoc()
{
}

BOOL CFontLogicalTWIPDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;

    // TODO: add reinitialization code here
    // (SDI documents will reuse this document)

    return TRUE;
}




// CFontLogicalTWIPDoc serialization

void CFontLogicalTWIPDoc::Serialize(CArchive& ar)
{
    if (ar.IsStoring()) {
        // TODO: add storing code here
    }
    else {
        // TODO: add loading code here
    }
}


// CFontLogicalTWIPDoc diagnostics

#ifdef _DEBUG
void CFontLogicalTWIPDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CFontLogicalTWIPDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG


// CFontLogicalTWIPDoc commands
