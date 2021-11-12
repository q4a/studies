// PersistFrm.h : interface of the CPersistFrame class
//


#pragma once

class AFX_EXT_CLASS CPersistFrame : public CFrameWnd {

protected: // create from serialization only
    CPersistFrame();
    DECLARE_DYNCREATE(CPersistFrame)

// Attributes
public:

// Operations
public:

// Overrides
public:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual void ActivateFrame(int nCmdShow = -1);

// Implementation
public:
    virtual ~CPersistFrame();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
    CStatusBar  m_wndStatusBar;
    CToolBar    m_wndToolBar;

// Generated message map functions
public:
    afx_msg void OnDestroy();

protected:
    DECLARE_MESSAGE_MAP()

private:
    static const CRect  RectDefault;
    static LPCTSTR      ProfileHeading;
    static LPCTSTR      ProfileRect;
    static LPCTSTR      ProfileMin;
    static LPCTSTR      ProfileMax;

    BOOL    m_FirstActive;
};


