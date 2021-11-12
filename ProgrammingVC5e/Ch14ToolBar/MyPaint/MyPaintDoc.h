// MyPaintDoc.h : interface of the CMyPaintDoc class
//


#pragma once


class CMyPaintDoc : public CDocument
{
protected: // create from serialization only
	CMyPaintDoc();
	DECLARE_DYNCREATE(CMyPaintDoc)

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
	virtual ~CMyPaintDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


