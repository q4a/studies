// DBufScrollView.h : interface of the CDBufScrollView class
//

#pragma once

class CDBufScrollView : public CScrollView {
protected: // create from serialization only
    CDBufScrollView();
    DECLARE_DYNCREATE(CDBufScrollView)

// Attributes
public:
    CDBufScrollDoc* GetDocument() const;

private:
    const CSize     m_sizeEllipse;
    CPoint          m_ptTopLeft;
    BOOL            m_bCaptured;
    CSize           m_sizeOffset;
    CDC*            m_pMemDC;
    CBitmap*        m_pBmp;

// Operations
public:

// Overrides
public:
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
    virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
    virtual ~CDBufScrollView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnPaint();
public:
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
public:
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
public:
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in DBufScrollView.cpp
inline CDBufScrollDoc* CDBufScrollView::GetDocument() const
{
    return reinterpret_cast<CDBufScrollDoc*>(m_pDocument);
}
#endif

