// HexView.h : interface of the CHexView class
//


#pragma once


class CHexView : public CScrollView {
protected:
    DECLARE_DYNCREATE(CHexView)

public:
    CHexView();

// Attributes
public:
    CPoemDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
    virtual void OnInitialUpdate(); // called first time after construct
    virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
    virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
    virtual ~CHexView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
    DECLARE_MESSAGE_MAP()

public:
    CRect   m_RectPrint;
};

#ifndef _DEBUG  // debug version in HexView.cpp
inline CPoemDoc* CHexView::GetDocument() const
{
    return reinterpret_cast<CPoemDoc*>(m_pDocument);
}
#endif

