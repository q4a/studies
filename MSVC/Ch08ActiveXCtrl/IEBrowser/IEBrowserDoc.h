// IEBrowserDoc.h : interface of the CIEBrowserDoc class
//


#pragma once


class CIEBrowserDoc : public CDocument {
protected: // create from serialization only
    CIEBrowserDoc();
    DECLARE_DYNCREATE(CIEBrowserDoc)

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
    virtual ~CIEBrowserDoc();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
    DECLARE_MESSAGE_MAP()
};


