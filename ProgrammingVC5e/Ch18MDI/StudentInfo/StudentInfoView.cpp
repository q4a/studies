// StudentInfoView.cpp : implementation of the CStudentInfoView class
//

#include "StdAfx.h"
#include "StudentInfo.h"

#include "StudentInfoDoc.h"
#include "StudentInfoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStudentInfoView

IMPLEMENT_DYNCREATE(CStudentInfoView, CFormView)

BEGIN_MESSAGE_MAP(CStudentInfoView, CFormView)
    ON_BN_CLICKED(IDC_CLEAR, &CStudentInfoView::OnBnClickedClear)
    ON_COMMAND(ID_STUDENT_HOME, &CStudentInfoView::OnStudentHome)
    ON_COMMAND(ID_STUDENT_END, &CStudentInfoView::OnStudentEnd)
    ON_COMMAND(ID_STUDENT_PREV, &CStudentInfoView::OnStudentPrev)
    ON_COMMAND(ID_STUDENT_NEXT, &CStudentInfoView::OnStudentNext)
    ON_COMMAND(ID_STUDENT_INS, &CStudentInfoView::OnStudentIns)
    ON_COMMAND(ID_STUDENT_DEL, &CStudentInfoView::OnStudentDel)
    ON_UPDATE_COMMAND_UI(ID_STUDENT_HOME, &CStudentInfoView::OnUpdateStudentHome)
    ON_UPDATE_COMMAND_UI(ID_STUDENT_END, &CStudentInfoView::OnUpdateStudentEnd)
    ON_UPDATE_COMMAND_UI(ID_STUDENT_DEL, &CStudentInfoView::OnUpdateStudentDel)
    ON_UPDATE_COMMAND_UI(ID_STUDENT_NEXT, &CStudentInfoView::OnUpdateStudentNext)
    ON_UPDATE_COMMAND_UI(ID_STUDENT_PREV, &CStudentInfoView::OnUpdateStudentPrev)
END_MESSAGE_MAP()

// CStudentInfoView construction/destruction

CStudentInfoView::CStudentInfoView() :
    CFormView(CStudentInfoView::IDD),
    m_Grade(0), m_Name(_T("")), m_StudentListPos(NULL)
{
    MYTRACE("Enter");
}

CStudentInfoView::~CStudentInfoView()
{
}

void CStudentInfoView::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_NAME, m_Name);
    DDV_MaxChars(pDX, m_Name, 20);
    DDX_Text(pDX, IDC_GRADE, m_Grade);
    DDV_MinMaxInt(pDX, m_Grade, 0, 100);
}

BOOL CStudentInfoView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs

    return CFormView::PreCreateWindow(cs);
}

void CStudentInfoView::OnInitialUpdate()
{
    MYTRACE("Enter");
    m_StudentList = GetDocument()->GetStudentList();    // CAUTION: 这句要放在 OnInitialUpdate 之前调用, 因为 OnInitialUpdate->OnUpdate
    CFormView::OnInitialUpdate();
    ResizeParentToFit();
}


// CStudentInfoView diagnostics

#ifdef _DEBUG
void CStudentInfoView::AssertValid() const
{
    CFormView::AssertValid();
}

void CStudentInfoView::Dump(CDumpContext& dc) const
{
    CFormView::Dump(dc);
}

CStudentInfoDoc* CStudentInfoView::GetDocument() const // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStudentInfoDoc)));
    return (CStudentInfoDoc*)m_pDocument;
}
#endif  // _DEBUG


// CStudentInfoView message handlers

void CStudentInfoView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
    MYTRACE("Enter");
    m_StudentListPos = m_StudentList->GetHeadPosition();
    GetEntry(m_StudentListPos); // Doc -> View
}

void CStudentInfoView::ClearEntry()
{
    m_Name = _T("");
    m_Grade= 0;
    UpdateData(FALSE);
    ((CDialog*) this)->GotoDlgCtrl(GetDlgItem(IDC_NAME));
}

void CStudentInfoView::InsertEntry(POSITION pos)
{
    if (UpdateData(TRUE)) {
        CStudent* stu = new CStudent(m_Name, m_Grade);
        m_StudentListPos = m_StudentList->InsertAfter(m_StudentListPos, stu);
    }
}

void CStudentInfoView::GetEntry(POSITION pos)
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

// CStudentInfoView message handlers

void CStudentInfoView::OnBnClickedClear()
{
    MYTRACE("Enter");
    ClearEntry();
}

void CStudentInfoView::OnStudentHome()
{
    MYTRACE("Enter");
    if (!m_StudentList->IsEmpty()) {
        m_StudentListPos = m_StudentList->GetHeadPosition();
        GetEntry(m_StudentListPos);
    }
}

void CStudentInfoView::OnStudentEnd()
{
    MYTRACE("Enter");
    if (!m_StudentList->IsEmpty()) {
        m_StudentListPos = m_StudentList->GetTailPosition();
        GetEntry(m_StudentListPos);
    }
}

void CStudentInfoView::OnStudentPrev()
{
    MYTRACE("Enter");
    POSITION pos = m_StudentListPos;
    if (pos != NULL) {
        m_StudentList->GetPrev(pos);
        if (pos != NULL) {
            GetEntry(pos);
            m_StudentListPos = pos;
        }
    }
}

void CStudentInfoView::OnStudentNext()
{
    MYTRACE("Enter");
    POSITION pos = m_StudentListPos;
    if (pos != NULL) {
        m_StudentList->GetNext(pos);
        if (pos != NULL) {
            GetEntry(pos);
            m_StudentListPos = pos;
        }
    }
}

void CStudentInfoView::OnStudentIns()
{
    MYTRACE("Enter");
    InsertEntry(m_StudentListPos);
    GetDocument()->SetModifiedFlag(TRUE);
    GetDocument()->UpdateAllViews(this);
}

void CStudentInfoView::OnStudentDel()
{
    MYTRACE("Enter");
    POSITION pos = m_StudentListPos;
    if (pos != NULL) {
        m_StudentList->GetNext(pos);
        if (pos == NULL) {
            pos = m_StudentList->GetHeadPosition();
            MYTRACE("CStudentInfoView::OnStudentDel: GetHeadPos = %ld", pos);
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

void CStudentInfoView::OnUpdateStudentHome(CCmdUI *pCmdUI)
{
    POSITION pos = m_StudentList->GetHeadPosition();
    pCmdUI->Enable(m_StudentListPos != NULL && pos != m_StudentListPos);
}

void CStudentInfoView::OnUpdateStudentEnd(CCmdUI *pCmdUI)
{
    POSITION pos = m_StudentList->GetTailPosition();
    pCmdUI->Enable(m_StudentListPos != NULL && pos != m_StudentListPos);
}

void CStudentInfoView::OnUpdateStudentDel(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(m_StudentListPos != NULL);
}

void CStudentInfoView::OnUpdateStudentNext(CCmdUI *pCmdUI)
{
    OnUpdateStudentEnd(pCmdUI);
}

void CStudentInfoView::OnUpdateStudentPrev(CCmdUI *pCmdUI)
{
    OnUpdateStudentHome(pCmdUI);
}
