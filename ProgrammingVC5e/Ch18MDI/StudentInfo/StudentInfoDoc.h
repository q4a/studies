// StudentInfoDoc.h : interface of the CStudentInfoDoc class
//


#pragma once

#include "Student.h"

class CStudentInfoDoc : public CDocument {
protected: // create from serialization only
    CStudentInfoDoc();
    DECLARE_DYNCREATE(CStudentInfoDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
    virtual BOOL OnNewDocument();
    virtual void Serialize(CArchive& ar);
    virtual void DeleteContents();
    virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);

// Implementation
    CStudentList* GetStudentList() {
        return &m_StudentList;
    }

public:
    virtual ~CStudentInfoDoc();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
public:
    afx_msg void OnEditClearAll();
    afx_msg void OnUpdateEditClearAll(CCmdUI *pCmdUI);
    afx_msg void OnUpdateFileSave(CCmdUI *pCmdUI);

protected:
    DECLARE_MESSAGE_MAP()

private:
    CStudentList m_StudentList;
};


