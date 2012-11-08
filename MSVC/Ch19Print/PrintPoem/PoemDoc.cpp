// PoemDoc.cpp : implementation of the CPoemDoc class
//

#include "StdAfx.h"
#include "PrintPoem.h"

#include "PoemDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPoemDoc

IMPLEMENT_DYNCREATE(CPoemDoc, CDocument)

BEGIN_MESSAGE_MAP(CPoemDoc, CDocument)
END_MESSAGE_MAP()


// CPoemDoc construction/destruction

CPoemDoc::CPoemDoc()
{
    // TODO: add one-time construction code here

}

CPoemDoc::~CPoemDoc()
{
}

BOOL CPoemDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;

    m_StringArray.SetSize(10);
    m_StringArray[0] = _T("The pennycandystore beyond the EI");
    m_StringArray[1] = _T("is where I first");
    m_StringArray[2] = _T("                fell in love");
    m_StringArray[3] = _T("                     with unreality");
    m_StringArray[4] = _T("Jellybeans glowed in the semi-gloom");
    m_StringArray[5] = _T("of that september afternoon");
    m_StringArray[6] = _T("A cat upon the counter moved among");
    m_StringArray[7] = _T("                       the licorice sticks");
    m_StringArray[8] = _T("                    and tootise rolls");
    m_StringArray[9] = _T("                  and Oh Boy Gum");

    return TRUE;
}




// CPoemDoc serialization

void CPoemDoc::Serialize(CArchive& ar)
{
    if (ar.IsStoring()) {
        // TODO: add storing code here
    }
    else {
        // TODO: add loading code here
    }
    m_StringArray.Serialize(ar);
}


// CPoemDoc diagnostics

#ifdef _DEBUG
void CPoemDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CPoemDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG


// CPoemDoc commands

void CPoemDoc::DeleteContents()
{
    m_StringArray.RemoveAll();
}
