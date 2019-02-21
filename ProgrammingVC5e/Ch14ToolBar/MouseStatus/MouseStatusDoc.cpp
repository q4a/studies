// MouseStatusDoc.cpp : implementation of the CMouseStatusDoc class
//

#include "StdAfx.h"
#include "MouseStatus.h"

#include "MouseStatusDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMouseStatusDoc

IMPLEMENT_DYNCREATE(CMouseStatusDoc, CDocument)

BEGIN_MESSAGE_MAP(CMouseStatusDoc, CDocument)
END_MESSAGE_MAP()


// CMouseStatusDoc construction/destruction

CMouseStatusDoc::CMouseStatusDoc()
{
	// TODO: add one-time construction code here

}

CMouseStatusDoc::~CMouseStatusDoc()
{
}

BOOL CMouseStatusDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMouseStatusDoc serialization

void CMouseStatusDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CMouseStatusDoc diagnostics

#ifdef _DEBUG
void CMouseStatusDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMouseStatusDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMouseStatusDoc commands
