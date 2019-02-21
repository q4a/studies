// StudentForm2Doc.h : interface of the CStudentForm2Doc class
//

#pragma once

#include "Student.h"

class CStudentForm2Doc : public CDocument {
protected: // create from serialization only
    CStudentForm2Doc();
    DECLARE_DYNCREATE(CStudentForm2Doc)

// Attributes
public:

// Operations
public:

// Overrides
public:
    virtual BOOL OnNewDocument();
    virtual void Serialize(CArchive& ar);
    virtual void DeleteContents();

// Implementation
public:
    virtual ~CStudentForm2Doc();

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

    CStudentList* GetStudentList() {
        return &m_StudentList;
    }

// Generated message map functions
public:
    afx_msg void OnEditClearAll();
    afx_msg void OnUpdateEditClearAll(CCmdUI *pCmdUI);

protected:
    DECLARE_MESSAGE_MAP()

private:
    CStudentList m_StudentList;
};
