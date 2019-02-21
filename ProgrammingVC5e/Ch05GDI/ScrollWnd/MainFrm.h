// MainFrm.h : CMainFrame 类的接口
//

#pragma once

class CMainFrame : public CFrameWnd {
protected: // 仅从序列化创建
    CMainFrame();

public:
    virtual ~CMainFrame();

    DECLARE_DYNCREATE(CMainFrame)

// 属性
public:

// 操作
public:

// 重写
public:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// 实现

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
    CStatusBar  m_wndStatusBar;
    CToolBar    m_wndToolBar;

// 生成的消息映射函数
protected:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
    afx_msg void OnViewApple();
    DECLARE_MESSAGE_MAP()

private:
    CImageList m_imglstIcon;
};
