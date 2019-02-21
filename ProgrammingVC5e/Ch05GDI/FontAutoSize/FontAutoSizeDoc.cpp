// FontAutoSizeDoc.cpp : implementation of the CFontAutoSizeDoc class
//

#include "StdAfx.h"
#include "FontAutoSize.h"

#include "FontAutoSizeDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFontAutoSizeDoc

IMPLEMENT_DYNCREATE(CFontAutoSizeDoc, CDocument)

BEGIN_MESSAGE_MAP(CFontAutoSizeDoc, CDocument)
END_MESSAGE_MAP()


// CFontAutoSizeDoc construction/destruction

CFontAutoSizeDoc::CFontAutoSizeDoc()
{
    // TODO: add one-time construction code here

}

CFontAutoSizeDoc::~CFontAutoSizeDoc()
{
}

BOOL CFontAutoSizeDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;

    // TODO: add reinitialization code here
    // (SDI documents will reuse this document)

    return TRUE;
}




// CFontAutoSizeDoc serialization

void CFontAutoSizeDoc::Serialize(CArchive& ar)
{
    if (ar.IsStoring()) {
        // TODO: add storing code here
    }
    else {
        // TODO: add loading code here
    }
}


// CFontAutoSizeDoc diagnostics

#ifdef _DEBUG
void CFontAutoSizeDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CFontAutoSizeDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG


// CFontAutoSizeDoc commands
