// PersistWndDoc.cpp : implementation of the CPersistWndDoc class
//

#include "StdAfx.h"
#include "PersistWnd.h"

#include "PersistWndDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPersistWndDoc

IMPLEMENT_DYNCREATE(CPersistWndDoc, CDocument)

BEGIN_MESSAGE_MAP(CPersistWndDoc, CDocument)
END_MESSAGE_MAP()


// CPersistWndDoc construction/destruction

CPersistWndDoc::CPersistWndDoc()
{
	// TODO: add one-time construction code here

}

CPersistWndDoc::~CPersistWndDoc()
{
}

BOOL CPersistWndDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CPersistWndDoc serialization

void CPersistWndDoc::Serialize(CArchive& ar)
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


// CPersistWndDoc diagnostics

#ifdef _DEBUG
void CPersistWndDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPersistWndDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPersistWndDoc commands
