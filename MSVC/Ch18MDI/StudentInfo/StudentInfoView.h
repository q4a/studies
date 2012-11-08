// StudentInfoView.h : interface of the CStudentInfoView class
//


#pragma once


class CStudentInfoView : public CFormView {
protected: // create from serialization only
    CStudentInfoView();
    DECLARE_DYNCREATE(CStudentInfoView)

public:
    enum { IDD = IDD_STUDENTINFO_FORM };

// Attributes
public:
    CStudentInfoDoc* GetDocument() const;

// Operations
protected:
    virtual void ClearEntry();
    virtual void InsertEntry(POSITION pos);
    virtual void GetEntry(POSITION pos);

// Overrides
public:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual void OnInitialUpdate(); // called first time after construct
    virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);

// Implementation
public:
    virtual ~CStudentInfoView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

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

#ifndef _DEBUG  // debug version in StudentInfoView.cpp
inline CStudentInfoDoc* CStudentInfoView::GetDocument() const
{
    return reinterpret_cast<CStudentInfoDoc*>(m_pDocument);
}
#endif

