// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once

class CMainFrame : public CFrameWnd {
protected: // �������л�����
    CMainFrame();

public:
    virtual ~CMainFrame();

    DECLARE_DYNCREATE(CMainFrame)

// ����
public:

// ����
public:

// ��д
public:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// ʵ��

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
    CStatusBar  m_wndStatusBar;
    CToolBar    m_wndToolBar;

// ���ɵ���Ϣӳ�亯��
protected:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
    afx_msg void OnViewApple();
    DECLARE_MESSAGE_MAP()

private:
    CImageList m_imglstIcon;
};
