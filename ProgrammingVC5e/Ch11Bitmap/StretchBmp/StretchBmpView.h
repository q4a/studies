// StretchBmpView.h : interface of the CStretchBmpView class
//

#pragma once

class CStretchBmpView : public CScrollView {
protected: // create from serialization only
    CStretchBmpView();
    DECLARE_DYNCREATE(CStretchBmpView)

// Attributes
public:
    CStretchBmpDoc* GetDocument() const;

private:
    CDC*        m_pMemDC;
    CBitmap*    m_pBmp;
    CSize       m_sizeSrc;  // 位图 .bmp 的像素大小, 设备坐标
    CSize       m_sizeDest; // m_sizeSrc 在逻辑坐标下的映射值

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
    virtual ~CStretchBmpView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

private:
    DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in StretchBmpView.cpp
inline CStretchBmpDoc* CStretchBmpView::GetDocument() const
{
    return reinterpret_cast<CStretchBmpDoc*>(m_pDocument);
}
#endif
