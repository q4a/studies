// DBufScrollDoc.h : interface of the CDBufScrollDoc class
//


#pragma once


class CDBufScrollDoc : public CDocument {
protected: // create from serialization only
    CDBufScrollDoc();
    DECLARE_DYNCREATE(CDBufScrollDoc)

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
    virtual ~CDBufScrollDoc();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
    DECLARE_MESSAGE_MAP()
};


