// RichEdit1Doc.h : interface of the CRichEdit1Doc class
//


#pragma once


class CRichEdit1Doc : public CDocument {
protected: // create from serialization only
    CRichEdit1Doc();
    DECLARE_DYNCREATE(CRichEdit1Doc)

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
    virtual ~CRichEdit1Doc();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif


private:
    DECLARE_MESSAGE_MAP()

public:
    CString m_Text;

private:
    static const _TCHAR* DEF_INIT_TEXT;
};


