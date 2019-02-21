// PersistWndDoc.h : interface of the CPersistWndDoc class
//


#pragma once


class CPersistWndDoc : public CDocument
{
protected: // create from serialization only
	CPersistWndDoc();
	DECLARE_DYNCREATE(CPersistWndDoc)

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
	virtual ~CPersistWndDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


