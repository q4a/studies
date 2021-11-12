// IEBrowserView.h : interface of the CIEBrowserView class
//


#pragma once


class CIEBrowserView : public CView {
protected: // create from serialization only
    CIEBrowserView();
    DECLARE_DYNCREATE(CIEBrowserView)

// Attributes
public:
    CIEBrowserDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
    virtual ~CIEBrowserView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
    DECLARE_MESSAGE_MAP()

    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);

    DECLARE_EVENTSINK_MAP()

    void OnBeforeNavigateExplore1(LPCTSTR URL, long Flags, LPCTSTR TargetFrameName,
                                  VARIANT* PostData, LPCTSTR Headers, BOOL* Cancel);
    void OnTitleChangeExplorer2(LPCTSTR Text);

private:
    static LPCTSTR SearchURL;

    CWebBrowser m_SearchBrowser;
    CWebBrowser m_TargetBrowser;

};

#ifndef _DEBUG  // debug version in IEBrowserView.cpp
inline CIEBrowserDoc* CIEBrowserView::GetDocument() const
{
    return reinterpret_cast<CIEBrowserDoc*>(m_pDocument);
}
#endif

