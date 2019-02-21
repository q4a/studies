// FontLogicalTWIPView.h : interface of the CFontLogicalTWIPView class
//

#pragma once

class CFontLogicalTWIPView : public CView {
protected: // create from serialization only
    CFontLogicalTWIPView();
    virtual ~CFontLogicalTWIPView();
    DECLARE_DYNCREATE(CFontLogicalTWIPView)

// Attributes
public:
    CFontLogicalTWIPDoc* GetDocument() const;

// Operations
public:

// Overrides
public:

    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);

// Implementation
public:

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

private:
    void ShowFont(CDC* pDC, IN OUT int& nPos, int nPoints);

// Generated message map functions
protected:
    DECLARE_MESSAGE_MAP()

};

#ifndef _DEBUG  // debug version in FontLogicalTWIPView.cpp
inline CFontLogicalTWIPDoc* CFontLogicalTWIPView::GetDocument() const
{
    return reinterpret_cast<CFontLogicalTWIPDoc*>(m_pDocument);
}
#endif
