// StudentForm2View.cpp : implementation of the CStudentForm2View class
//

#include "StdAfx.h"
#include "StudentForm2.h"

#include "StudentForm2Doc.h"
#include "StudentForm2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CStudentForm2View

IMPLEMENT_DYNCREATE(CStudentForm2View, CFormView)

BEGIN_MESSAGE_MAP(CStudentForm2View, CFormView)
    ON_BN_CLICKED(IDC_CLEAR, &CStudentForm2View::OnBnClickedClear)
    ON_COMMAND(ID_STUDENT_HOME, &CStudentForm2View::OnStudentHome)
    ON_COMMAND(ID_STUDENT_END, &CStudentForm2View::OnStudentEnd)
    ON_COMMAND(ID_STUDENT_PREV, &CStudentForm2View::OnStudentPrev)
    ON_COMMAND(ID_STUDENT_NEXT, &CStudentForm2View::OnStudentNext)
    ON_COMMAND(ID_STUDENT_INS, &CStudentForm2View::OnStudentIns)
    ON_COMMAND(ID_STUDENT_DEL, &CStudentForm2View::OnStudentDel)
    ON_UPDATE_COMMAND_UI(ID_STUDENT_HOME, &CStudentForm2View::OnUpdateStudentHome)
    ON_UPDATE_COMMAND_UI(ID_STUDENT_END, &CStudentForm2View::OnUpdateStudentEnd)
    ON_UPDATE_COMMAND_UI(ID_STUDENT_DEL, &CStudentForm2View::OnUpdateStudentDel)
    ON_UPDATE_COMMAND_UI(ID_STUDENT_NEXT, &CStudentForm2View::OnUpdateStudentNext)
    ON_UPDATE_COMMAND_UI(ID_STUDENT_PREV, &CStudentForm2View::OnUpdateStudentPrev)
END_MESSAGE_MAP()

// CStudentForm2View construction/destruction

CStudentForm2View::CStudentForm2View() :
    CFormView(CStudentForm2View::IDD),
    m_Grade(0), m_Name(_T("")), m_StudentListPos(NULL)
{
    MYTRACE("CStudentForm2View ctor");
}

CStudentForm2View::~CStudentForm2View()
{
}

void CStudentForm2View::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_NAME, m_Name);
    DDV_MaxChars(pDX, m_Name, 20);
    DDX_Text(pDX, IDC_GRADE, m_Grade);
    DDV_MinMaxInt(pDX, m_Grade, 0, 100);
}

BOOL CStudentForm2View::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs

    return CFormView::PreCreateWindow(cs);
}

void CStudentForm2View::OnInitialUpdate()
{
    MYTRACE("CStudentForm2View::OnInitialUpdate");
    m_StudentList = GetDocument()->GetStudentList();    // CAUTION: 这句要放在 OnInitialUpdate 之前调用, 因为 OnInitialUpdate->OnUpdate
    CFormView::OnInitialUpdate();
    GetParentFrame()->RecalcLayout();
    ResizeParentToFit();
}

// CStudentForm2View diagnostics

#ifdef _DEBUG
void CStudentForm2View::AssertValid() const
{
    CFormView::AssertValid();
}

void CStudentForm2View::Dump(CDumpContext& dc) const
{
    CFormView::Dump(dc);
}

CStudentForm2Doc* CStudentForm2View::GetDocument() const // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStudentForm2Doc)));
    return (CStudentForm2Doc*) m_pDocument;
}
#endif  // _DEBUG

void CStudentForm2View::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
    MYTRACE("CStudentForm2View::OnUpdate");
    m_StudentListPos = m_StudentList->GetHeadPosition();
    GetEntry(m_StudentListPos); // Doc -> View
}

void CStudentForm2View::ClearEntry()
{
    m_Name = _T("");
    m_Grade= 0;
    UpdateData(FALSE);
    ((CDialog*) this)->GotoDlgCtrl(GetDlgItem(IDC_NAME));
}

void CStudentForm2View::InsertEntry(POSITION pos)
{
    if (UpdateData(TRUE)) {
        CStudent* stu = new CStudent(m_Name, m_Grade);
        m_StudentListPos = m_StudentList->InsertAfter(m_StudentListPos, stu);
    }
}

void CStudentForm2View::GetEntry(POSITION pos)
{
    if (pos != NULL) {
        CStudent* stu = m_StudentList->GetAt(pos);
        m_Name = stu->m_Name;
        m_Grade = stu->m_Grade;
    }
    else
        ClearEntry();
    UpdateData(FALSE);
}

// CStudentForm2View message handlers

void CStudentForm2View::OnBnClickedClear()
{
    MYTRACE("CStudentForm2View::OnBnClickedClear");
    ClearEntry();
}

void CStudentForm2View::OnStudentHome()
{
    MYTRACE("CStudentForm2View::OnStudentHome");
    if (!m_StudentList->IsEmpty()) {
        m_StudentListPos = m_StudentList->GetHeadPosition();
        GetEntry(m_StudentListPos);
    }
}

void CStudentForm2View::OnStudentEnd()
{
    MYTRACE("CStudentForm2View::OnStudentEnd");
    if (!m_StudentList->IsEmpty()) {
        m_StudentListPos = m_StudentList->GetTailPosition();
        GetEntry(m_StudentListPos);
    }
}

void CStudentForm2View::OnStudentPrev()
{
    MYTRACE("CStudentForm2View::OnStudentPrev");
    POSITION pos = m_StudentListPos;
    if (pos != NULL) {
        m_StudentList->GetPrev(pos);
        if (pos != NULL) {
            GetEntry(pos);
            m_StudentListPos = pos;
        }
    }
}

void CStudentForm2View::OnStudentNext()
{
    MYTRACE("CStudentForm2View::OnStudentNext");
    POSITION pos = m_StudentListPos;
    if (pos != NULL) {
        m_StudentList->GetNext(pos);
        if (pos != NULL) {
            GetEntry(pos);
            m_StudentListPos = pos;
        }
    }
}

void CStudentForm2View::OnStudentIns()
{
    MYTRACE("CStudentForm2View::OnStudentIns");
    InsertEntry(m_StudentListPos);
    GetDocument()->SetModifiedFlag(TRUE);
    GetDocument()->UpdateAllViews(this);
}

void CStudentForm2View::OnStudentDel()
{
    MYTRACE("CStudentForm2View::OnStudentDel");
    POSITION pos = m_StudentListPos;
    if (pos != NULL) {
        m_StudentList->GetNext(pos);
        if (pos == NULL) {
            pos = m_StudentList->GetHeadPosition();
            MYTRACE("CStudentForm2View::OnStudentDel: GetHeadPos = %ld", pos);
            if (pos == m_StudentListPos)
                pos = NULL;
        }
    }

    GetEntry(pos);
    CStudent* pos2 = m_StudentList->GetAt(m_StudentListPos);
    m_StudentList->RemoveAt(m_StudentListPos);
    delete pos2;
    m_StudentListPos = pos;
    GetDocument()->SetModifiedFlag(TRUE);
    GetDocument()->UpdateAllViews(this);
}

void CStudentForm2View::OnUpdateStudentHome(CCmdUI *pCmdUI)
{
    POSITION pos = m_StudentList->GetHeadPosition();
    pCmdUI->Enable(m_StudentListPos != NULL && pos != m_StudentListPos);
}

void CStudentForm2View::OnUpdateStudentEnd(CCmdUI *pCmdUI)
{
    POSITION pos = m_StudentList->GetTailPosition();
    pCmdUI->Enable(m_StudentListPos != NULL && pos != m_StudentListPos);
}

void CStudentForm2View::OnUpdateStudentDel(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(m_StudentListPos != NULL);
}

void CStudentForm2View::OnUpdateStudentNext(CCmdUI *pCmdUI)
{
    OnUpdateStudentEnd(pCmdUI);
}

void CStudentForm2View::OnUpdateStudentPrev(CCmdUI *pCmdUI)
{
    OnUpdateStudentHome(pCmdUI);
}
