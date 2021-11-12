// StudentForm2View.h : interface of the CStudentForm2View class
//

#pragma once

class CStudentForm2View : public CFormView {
protected: // create from serialization only
    CStudentForm2View();
    DECLARE_DYNCREATE(CStudentForm2View)

public:
    enum { IDD = IDD_STUDENTFORM2_FORM };

// Attributes
public:
    CStudentForm2Doc* GetDocument() const;

protected:
    virtual void ClearEntry();
    virtual void InsertEntry(POSITION pos);
    virtual void GetEntry(POSITION pos);

// Operations
public:

// Overrides
public:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual void OnInitialUpdate(); // called first time after construct
    virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);

// Implementation
public:
    virtual ~CStudentForm2View();

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
public:
    afx_msg void OnBnClickedClear();
    afx_msg void OnStudentHome();
    afx_msg void OnStudentEnd();
    afx_msg void OnStudentPrev();
    afx_msg void OnStudentNext();
    afx_msg void OnStudentIns();
    afx_msg void OnStudentDel();
    afx_msg void OnUpdateStudentHome(CCmdUI *pCmdUI);
    afx_msg void OnUpdateStudentEnd(CCmdUI *pCmdUI);
    afx_msg void OnUpdateStudentDel(CCmdUI *pCmdUI);
    afx_msg void OnUpdateStudentNext(CCmdUI *pCmdUI);
    afx_msg void OnUpdateStudentPrev(CCmdUI *pCmdUI);

protected:
    DECLARE_MESSAGE_MAP()

public:
    CString m_Name;
    int     m_Grade;

protected:
    POSITION        m_StudentListPos;
    CStudentList*   m_StudentList;
};

#ifndef _DEBUG  // debug version in StudentForm2View.cpp
inline CStudentForm2Doc* CStudentForm2View::GetDocument() const
{
    return reinterpret_cast<CStudentForm2Doc*>(m_pDocument);
}
#endif

