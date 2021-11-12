// BmpResView.h : interface of the CBmpResView class
//


#pragma once


class CBmpResView : public CView {
protected: // create from serialization only
    CBmpResView();
    DECLARE_DYNCREATE(CBmpResView)

// Attributes
public:
    CBmpResDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
    virtual ~CBmpResView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
    DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in BmpResView.cpp
inline CBmpResDoc* CBmpResView::GetDocument() const
{
    return reinterpret_cast<CBmpResDoc*>(m_pDocument);
}
#endif

