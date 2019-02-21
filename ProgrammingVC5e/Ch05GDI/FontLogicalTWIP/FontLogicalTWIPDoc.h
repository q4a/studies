// FontLogicalTWIPDoc.h : interface of the CFontLogicalTWIPDoc class
//


#pragma once


class CFontLogicalTWIPDoc : public CDocument {
protected: // create from serialization only
    CFontLogicalTWIPDoc();
    DECLARE_DYNCREATE(CFontLogicalTWIPDoc)

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
    virtual ~CFontLogicalTWIPDoc();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
    DECLARE_MESSAGE_MAP()
};


