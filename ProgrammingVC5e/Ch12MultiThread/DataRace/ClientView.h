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

////////////////////////////////////////////////////////////////////////////////
// 主框架窗口客户区类 CClientView
////////////////////////////////////////////////////////////////////////////////

class CClientView : public CWnd {
public:
    CClientView() : m_Ellipse(100, 100, 200, 200), m_Color(GRAY_BRUSH), m_Text(_T("")) {}
    virtual ~CClientView() {}

public:
    void SetShowText(const CString& text) {
        m_Text = text;
    }

private:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = 0);
    virtual void OnDraw(CDC* pDC);

private:
    // 消息处理

    afx_msg void OnPaint();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

    DECLARE_MESSAGE_MAP()

private:
    UINT    m_Color;
    CRect   m_Ellipse;
    CString m_Text;
};

#endif  // __CLIENTVIEW_H__
