// MyPaintDoc.cpp : implementation of the CMyPaintDoc class
//

#include "StdAfx.h"
#include "MyPaint.h"

#include "MyPaintDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyPaintDoc

IMPLEMENT_DYNCREATE(CMyPaintDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyPaintDoc, CDocument)
END_MESSAGE_MAP()


// CMyPaintDoc construction/destruction

CMyPaintDoc::CMyPaintDoc()
{
	// TODO: add one-time construction code here

}

CMyPaintDoc::~CMyPaintDoc()
{
}

BOOL CMyPaintDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMyPaintDoc serialization

void CMyPaintDoc::Serialize(CArchive& ar)
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


// CMyPaintDoc diagnostics

#ifdef _DEBUG
void CMyPaintDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyPaintDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMyPaintDoc commands
