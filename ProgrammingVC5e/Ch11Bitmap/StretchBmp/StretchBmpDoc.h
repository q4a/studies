// StretchBmpDoc.h : interface of the CStretchBmpDoc class
//


#pragma once


class CStretchBmpDoc : public CDocument {
protected: // create from serialization only
    CStretchBmpDoc();
    DECLARE_DYNCREATE(CStretchBmpDoc)

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
    virtual ~CStretchBmpDoc();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
    DECLARE_MESSAGE_MAP()
};
