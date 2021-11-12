// StudentForm2Doc.cpp : implementation of the CStudentForm2Doc class
//

#include "StdAfx.h"
#include "StudentForm2.h"

#include "StudentForm2Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStudentForm2Doc

IMPLEMENT_DYNCREATE(CStudentForm2Doc, CDocument)

BEGIN_MESSAGE_MAP(CStudentForm2Doc, CDocument)
    ON_COMMAND(ID_EDIT_CLEAR_ALL, &CStudentForm2Doc::OnEditClearAll)
    ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR_ALL, &CStudentForm2Doc::OnUpdateEditClearAll)
END_MESSAGE_MAP()


// CStudentForm2Doc construction/destruction

CStudentForm2Doc::CStudentForm2Doc()
{
    MYTRACE("CStudentForm2Doc ctor");
#ifdef _DEBUG
    afxDump.SetDepth(1);
#endif
}

CStudentForm2Doc::~CStudentForm2Doc()
{
#ifdef _DEBUG
    Dump(afxDump);
#endif  // _DEBUG
}

BOOL CStudentForm2Doc::OnNewDocument()
{
    MYTRACE("CStudentForm2Doc::OnNewDocument");
    if (!CDocument::OnNewDocument())
        return FALSE;

    // TODO: add reinitialization code here
    // (SDI documents will reuse this document)

    return TRUE;
}

// CStudentForm2Doc serialization

void CStudentForm2Doc::Serialize(CArchive& ar)
{
    if (ar.IsStoring()) {
        // TODO: add storing code here
    }
    else {
        // TODO: add loading code here
    }
}


// CStudentForm2Doc diagnostics

#ifdef _DEBUG
void CStudentForm2Doc::AssertValid() const
{
    CDocument::AssertValid();
}

void CStudentForm2Doc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
    dc << m_StudentList << _T("\n");
}
#endif  // _DEBUG


// CStudentForm2Doc commands

void CStudentForm2Doc::DeleteContents()
{
#ifdef _DEBUG
    Dump(afxDump);
#endif

    while (m_StudentList.GetHeadPosition())
        delete m_StudentList.RemoveHead();
}

void CStudentForm2Doc::OnEditClearAll()
{
    DeleteContents();
    UpdateAllViews(NULL);
}

void CStudentForm2Doc::OnUpdateEditClearAll(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(!m_StudentList.IsEmpty());
}
