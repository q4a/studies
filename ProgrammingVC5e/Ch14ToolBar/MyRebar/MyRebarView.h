// MyRebarView.h : interface of the CMyRebarView class
//


#pragma once


class CMyRebarView : public CView
{
protected: // create from serialization only
	CMyRebarView();
	DECLARE_DYNCREATE(CMyRebarView)

// Attributes
public:
	CMyRebarDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CMyRebarView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MyRebarView.cpp
inline CMyRebarDoc* CMyRebarView::GetDocument() const
   { return reinterpret_cast<CMyRebarDoc*>(m_pDocument); }
#endif

