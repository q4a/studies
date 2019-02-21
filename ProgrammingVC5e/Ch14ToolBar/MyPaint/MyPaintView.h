// MyPaintView.h : interface of the CMyPaintView class
//


#pragma once


class CMyPaintView : public CView {
protected: // create from serialization only
    CMyPaintView();
    DECLARE_DYNCREATE(CMyPaintView)

// Attributes
public:
    CMyPaintDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
    virtual ~CMyPaintView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
public:
    afx_msg void OnDrawCircle();
    afx_msg void OnUpdateDrawCircle(CCmdUI *pCmdUI);
    afx_msg void OnDrawPattern();
    afx_msg void OnUpdateDrawPattern(CCmdUI *pCmdUI);
    afx_msg void OnDrawSquare();
    afx_msg void OnUpdateDrawSquare(CCmdUI *pCmdUI);

protected:
    DECLARE_MESSAGE_MAP()

private:
    CRect   m_Rect;
    BOOL    m_Circle;
    BOOL    m_Pattern;
};

#ifndef _DEBUG  // debug version in MyPaintView.cpp
inline CMyPaintDoc* CMyPaintView::GetDocument() const
{
    return reinterpret_cast<CMyPaintDoc*>(m_pDocument);
}
#endif

