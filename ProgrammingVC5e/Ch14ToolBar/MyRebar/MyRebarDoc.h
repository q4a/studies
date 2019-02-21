// MyRebarDoc.h : interface of the CMyRebarDoc class
//


#pragma once


class CMyRebarDoc : public CDocument
{
protected: // create from serialization only
	CMyRebarDoc();
	DECLARE_DYNCREATE(CMyRebarDoc)

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
	virtual ~CMyRebarDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


