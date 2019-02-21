// BmpResDoc.h : interface of the CBmpResDoc class
//


#pragma once


class CBmpResDoc : public CDocument {
protected: // create from serialization only
    CBmpResDoc();
    DECLARE_DYNCREATE(CBmpResDoc)

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
    virtual ~CBmpResDoc();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
    DECLARE_MESSAGE_MAP()
};


