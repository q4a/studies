// StudentFormView.h : interface of the CStudentFormView class
//


#pragma once


class CStudentFormView : public CFormView {
protected: // create from serialization only
    CStudentFormView();
    DECLARE_DYNCREATE(CStudentFormView)

public:
    enum { IDD = IDD_STUDENTFORM_FORM };

// Attributes
public:
    CStudentFormDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
    virtual ~CStudentFormView();

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
    DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnBnClickedEnter();
    afx_msg void OnEditClearAll();
    afx_msg void OnUpdateEditClearAll(CCmdUI *pCmdUI);

private:
    void UpdateControlsFromDoc();

public:
    CString m_Name;
    int m_Grade;
};

#ifndef _DEBUG  // debug version in StudentFormView.cpp
inline CStudentFormDoc* CStudentFormView::GetDocument() const
{
    return reinterpret_cast<CStudentFormDoc*>(m_pDocument);
}
#endif

