// PersistWndView.h : interface of the CPersistWndView class
//


#pragma once


class CPersistWndView : public CView
{
protected: // create from serialization only
	CPersistWndView();
	DECLARE_DYNCREATE(CPersistWndView)

// Attributes
public:
	CPersistWndDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CPersistWndView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PersistWndView.cpp
inline CPersistWndDoc* CPersistWndView::GetDocument() const
   { return reinterpret_cast<CPersistWndDoc*>(m_pDocument); }
#endif

