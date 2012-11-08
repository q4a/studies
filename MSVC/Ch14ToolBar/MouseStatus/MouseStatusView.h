// MouseStatusView.h : interface of the CMouseStatusView class
//


#pragma once


class CMouseStatusView : public CView {
protected: // create from serialization only
    CMouseStatusView();
    DECLARE_DYNCREATE(CMouseStatusView)

// Attributes
public:
    CMouseStatusDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
    virtual ~CMouseStatusView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
public:
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);

protected:
    DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MouseStatusView.cpp
inline CMouseStatusDoc* CMouseStatusView::GetDocument() const
{
    return reinterpret_cast<CMouseStatusDoc*>(m_pDocument);
}
#endif

