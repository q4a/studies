// MainFrm.h : interface of the CMainFrame class
//


#pragma once

class CMainFrame : public CFrameWnd {

protected: // create from serialization only
    CMainFrame();
    DECLARE_DYNCREATE(CMainFrame)

private:
    enum VIEW_TYPE {
        VIEW_STRING = 1,
        VIEW_HEX    = 2
    };

// Attributes
public:

// Operations
private:
    void SwitchToView(VIEW_TYPE viewType);

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

protected:  // control bar embedded members
    CStatusBar  m_wndStatusBar;
    CToolBar    m_wndToolBar;

// Generated message map functions
public:
    afx_msg void OnViewStringView();
    afx_msg void OnUpdateViewStringView(CCmdUI *pCmdUI);
    afx_msg void OnViewHexView();
    afx_msg void OnUpdateViewHexView(CCmdUI *pCmdUI);

protected:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    DECLARE_MESSAGE_MAP()
};


