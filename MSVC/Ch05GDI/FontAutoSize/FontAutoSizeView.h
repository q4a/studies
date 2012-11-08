// FontAutoSizeView.h : interface of the CFontAutoSizeView class
//


#pragma once


class CFontAutoSizeView : public CView {
protected: // create from serialization only
    CFontAutoSizeView();
    virtual ~CFontAutoSizeView();

    DECLARE_DYNCREATE(CFontAutoSizeView)

// Attributes
public:
    CFontAutoSizeDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

private:
    void TraceMetrics(CDC* pDC);

// Generated message map functions

public:
    virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);

protected:
    DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FontAutoSizeView.cpp
inline CFontAutoSizeDoc* CFontAutoSizeView::GetDocument() const
{
    return reinterpret_cast<CFontAutoSizeDoc*>(m_pDocument);
}
#endif

