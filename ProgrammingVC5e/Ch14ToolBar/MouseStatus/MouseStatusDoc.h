// MouseStatusDoc.h : interface of the CMouseStatusDoc class
//


#pragma once


class CMouseStatusDoc : public CDocument
{
protected: // create from serialization only
	CMouseStatusDoc();
	DECLARE_DYNCREATE(CMouseStatusDoc)

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
	virtual ~CMouseStatusDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


