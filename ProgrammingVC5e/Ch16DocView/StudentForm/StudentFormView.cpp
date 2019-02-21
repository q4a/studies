// StudentFormView.cpp : implementation of the CStudentFormView class
//

#include "StdAfx.h"
#include "StudentForm.h"

#include "StudentFormDoc.h"
#include "StudentFormView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStudentFormView

IMPLEMENT_DYNCREATE(CStudentFormView, CFormView)

BEGIN_MESSAGE_MAP(CStudentFormView, CFormView)
    ON_BN_CLICKED(IDC_ENTER, &CStudentFormView::OnBnClickedEnter)
    ON_COMMAND(ID_EDIT_CLEAR_ALL, &CStudentFormView::OnEditClearAll)
    ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR_ALL, &CStudentFormView::OnUpdateEditClearAll)
END_MESSAGE_MAP()

// CStudentFormView construction/destruction

CStudentFormView::CStudentFormView()
    : CFormView(CStudentFormView::IDD), m_Grade(0), m_Name(_T(""))
{
}

CStudentFormView::~CStudentFormView()
{
}

void CStudentFormView::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_NAME, m_Name);
    DDX_Text(pDX, IDC_GRADE, m_Grade);
    DDV_MinMaxInt(pDX, m_Grade, 0, 100);
}

BOOL CStudentFormView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs

    return CFormView::PreCreateWindow(cs);
}

void CStudentFormView::OnInitialUpdate()
{
    CFormView::OnInitialUpdate();
    GetParentFrame()->RecalcLayout();
    ResizeParentToFit();
    UpdateControlsFromDoc();
}

void CStudentFormView::UpdateControlsFromDoc()
{
    CStudentFormDoc* doc = GetDocument();
    m_Grade = doc->m_Student.m_Grade;
    m_Name = doc->m_Student.m_Name;
    UpdateData(FALSE);
}

// CStudentFormView diagnostics

#ifdef _DEBUG
void CStudentFormView::AssertValid() const
{
    CFormView::AssertValid();
}

void CStudentFormView::Dump(CDumpContext& dc) const
{
    CFormView::Dump(dc);
}

CStudentFormDoc* CStudentFormView::GetDocument() const // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStudentFormDoc)));
    return (CStudentFormDoc*) m_pDocument;
}
#endif //_DEBUG


// CStudentFormView message handlers

void CStudentFormView::OnBnClickedEnter()
{
    CStudentFormDoc* doc = GetDocument();
    UpdateData(TRUE);
    doc->m_Student.m_Grade = m_Grade;
    doc->m_Student.m_Name = m_Name;
}

void CStudentFormView::OnEditClearAll()
{
    GetDocument()->m_Student.SetEmpty();
    UpdateControlsFromDoc();
}

void CStudentFormView::OnUpdateEditClearAll(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(!GetDocument()->m_Student.IsEmpty());
}
