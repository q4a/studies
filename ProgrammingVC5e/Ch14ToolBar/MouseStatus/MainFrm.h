// MainFrm.h : interface of the CMainFrame class
//


#pragma once

class CMainFrame : public CFrameWnd {

protected: // create from serialization only
    CMainFrame();
    DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
public:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
    virtual ~CMainFrame();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

public:
    CStatusBar  m_wndStatusBar;

protected:
    CToolBar    m_wndToolBar;

// Generated message map functions
public:
    afx_msg void OnViewStatusBar();
    afx_msg void OnUpdateViewStatusBar(CCmdUI *pCmdUI);
    afx_msg void OnUpdateLeft(CCmdUI *pCmdUI);
    afx_msg void OnUpdateRight(CCmdUI *pCmdUI);

protected:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    DECLARE_MESSAGE_MAP()
};


