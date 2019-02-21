////////////////////////////////////////////////////////////////////////////////
// 文    件 : ClientView.h
// 功能说明 :
//   主框架窗口客户区
//
// 版    本 : 1.0
// 作    者 : Breaker Zhao <breaker.zy_AT_gmail>
// 日    期 : 2010-10
////////////////////////////////////////////////////////////////////////////////

#ifndef __CLIENTVIEW_H__
#define __CLIENTVIEW_H__

class CDib;

////////////////////////////////////////////////////////////////////////////////
// 主框架窗口客户区类 CClientView
////////////////////////////////////////////////////////////////////////////////

class CClientView : public CWnd {
public:
    CClientView();
    virtual ~CClientView();

public:
    BOOL LoadBmp(const TCHAR* path);

private:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = 0);
    virtual void OnDraw(CDC* pDC);

private:
    // 消息处理

    afx_msg void OnPaint();

    DECLARE_MESSAGE_MAP()

private:
    CDib*       m_Dib;
};

#endif  // __CLIENTVIEW_H__
