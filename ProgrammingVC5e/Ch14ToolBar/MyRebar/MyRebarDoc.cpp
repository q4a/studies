// MyRebarDoc.cpp : implementation of the CMyRebarDoc class
//

#include "StdAfx.h"
#include "MyRebar.h"

#include "MyRebarDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyRebarDoc

IMPLEMENT_DYNCREATE(CMyRebarDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyRebarDoc, CDocument)
END_MESSAGE_MAP()


// CMyRebarDoc construction/destruction

CMyRebarDoc::CMyRebarDoc()
{
	// TODO: add one-time construction code here

}

CMyRebarDoc::~CMyRebarDoc()
{
}

BOOL CMyRebarDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMyRebarDoc serialization

void CMyRebarDoc::Serialize(CArchive& ar)
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


// CMyRebarDoc diagnostics

#ifdef _DEBUG
void CMyRebarDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyRebarDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMyRebarDoc commands
