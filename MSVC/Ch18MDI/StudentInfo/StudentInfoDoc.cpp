// StudentInfoDoc.cpp : implementation of the CStudentInfoDoc class
//

#include "StdAfx.h"
#include "StudentInfo.h"

#include "StudentInfoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStudentInfoDoc

IMPLEMENT_DYNCREATE(CStudentInfoDoc, CDocument)

BEGIN_MESSAGE_MAP(CStudentInfoDoc, CDocument)
    ON_COMMAND(ID_EDIT_CLEAR_ALL, &CStudentInfoDoc::OnEditClearAll)
    ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR_ALL, &CStudentInfoDoc::OnUpdateEditClearAll)
    ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, &CStudentInfoDoc::OnUpdateFileSave)
END_MESSAGE_MAP()


// CStudentInfoDoc construction/destruction

CStudentInfoDoc::CStudentInfoDoc()
{
    MYTRACE("Enter");
    DEBUG_ONLY(afxDump.SetDepth(1));
}

CStudentInfoDoc::~CStudentInfoDoc()
{
    DEBUG_ONLY(Dump(afxDump));
}

BOOL CStudentInfoDoc::OnNewDocument()
{
    MYTRACE("Enter");
    if (!CDocument::OnNewDocument())
        return FALSE;

    // TODO: add reinitialization code here
    // (SDI documents will reuse this document)

    return TRUE;
}

// CStudentInfoDoc serialization

void CStudentInfoDoc::Serialize(CArchive& ar)
{
    MYTRACE("Enter");
    if (ar.IsStoring()) {
        // TODO: add storing code here
    }
    else {
        // TODO: add loading code here
    }
    m_StudentList.Serialize(ar);
}


// CStudentInfoDoc diagnostics

#ifdef _DEBUG
void CStudentInfoDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CStudentInfoDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif  // _DEBUG


// CStudentInfoDoc commands

void CStudentInfoDoc::DeleteContents()
{
    MYTRACE("Enter");
    while (m_StudentList.GetHeadPosition())
        delete m_StudentList.RemoveHead();
}

void CStudentInfoDoc::OnEditClearAll()
{
    DeleteContents();
    UpdateAllViews(NULL);
}

void CStudentInfoDoc::OnUpdateEditClearAll(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(!m_StudentList.IsEmpty());
}

BOOL CStudentInfoDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
    MYTRACE("Enter");
    if (!CDocument::OnOpenDocument(lpszPathName))
        return FALSE;

    // TODO:  Add your specialized creation code here

    return TRUE;
}

void CStudentInfoDoc::OnUpdateFileSave(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(this->IsModified());
}
