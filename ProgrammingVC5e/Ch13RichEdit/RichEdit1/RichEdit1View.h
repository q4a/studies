// RichEdit1View.h : interface of the CRichEdit1View class
//

#pragma once

class CRichEdit1View : public CView {
protected: // create from serialization only
    CRichEdit1View();
    DECLARE_DYNCREATE(CRichEdit1View)

// Attributes
public:
    CRichEdit1Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
    virtual void OnInitialUpdate();

// Implementation
public:
    virtual ~CRichEdit1View();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

private:
    afx_msg void OnGetSelFormat();
    afx_msg void OnSetSelFormat();
    afx_msg void OnTransferGetdata();
    afx_msg void OnTransferStoredata();
    afx_msg void OnUpdateTransferStoredata(CCmdUI *pCmdUI);
    afx_msg void OnEditClearAll();
    afx_msg void OnUpdateEditClearAll(CCmdUI *pCmdUI);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnFormatDefault();
    afx_msg void OnFormatSelection();
    afx_msg void OnUpdateFormatSelection(CCmdUI *pCmdUI);
    afx_msg LRESULT OnUserApply(WPARAM wparam, LPARAM lparam);

    DECLARE_MESSAGE_MAP()

private:
    void GetFormat(CHARFORMAT2& cf);

private:
    CRichEditCtrl   m_RichEdit;
    CFontSheet      m_FontSheet;
    enum FORMAT_TYPE { FORMAT_DEFAULT, FORMAT_SELECT } m_FormatType;
};

#ifndef _DEBUG  // debug version in RichEdit1View.cpp
inline CRichEdit1Doc* CRichEdit1View::GetDocument() const
{
    return reinterpret_cast<CRichEdit1Doc*>(m_pDocument);
}
#endif
