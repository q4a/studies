// StudentFormDoc.cpp : implementation of the CStudentFormDoc class
//

#include "StdAfx.h"
#include "StudentForm.h"

#include "StudentFormDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStudentFormDoc

IMPLEMENT_DYNCREATE(CStudentFormDoc, CDocument)

BEGIN_MESSAGE_MAP(CStudentFormDoc, CDocument)
END_MESSAGE_MAP()


// CStudentFormDoc construction/destruction

CStudentFormDoc::CStudentFormDoc() : m_Student(_T("No Name"), 0)
{
}

CStudentFormDoc::~CStudentFormDoc()
{
#ifdef _DEBUG
    Dump(afxDump);
#endif  // _DEBUG
}

BOOL CStudentFormDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;

    // TODO: add reinitialization code here
    // (SDI documents will reuse this document)

    return TRUE;
}

// CStudentFormDoc serialization

void CStudentFormDoc::Serialize(CArchive& ar)
{
    if (ar.IsStoring()) {
        // TODO: add storing code here
    }
    else {
        // TODO: add loading code here
    }
}


// CStudentFormDoc diagnostics

#ifdef _DEBUG
void CStudentFormDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CStudentFormDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
    dc << m_Student << _T("\n");
}
#endif //_DEBUG


// CStudentFormDoc commands
