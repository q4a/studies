// StudentFormDoc.h : interface of the CStudentFormDoc class
//

#pragma once

#include "Student.h"

class CStudentFormDoc : public CDocument {
protected: // create from serialization only
    CStudentFormDoc();
    DECLARE_DYNCREATE(CStudentFormDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
    virtual BOOL OnNewDocument();
    virtual void Serialize(CArchive& ar);

// Implementation
public:
    virtual ~CStudentFormDoc();

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
    DECLARE_MESSAGE_MAP()

public:
    CStudent    m_Student;
};
