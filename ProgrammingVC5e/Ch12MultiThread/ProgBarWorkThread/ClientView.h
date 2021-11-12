////////////////////////////////////////////////////////////////////////////////
// ��    �� : ClientView.h
// ����˵�� :
//   ����ܴ��ڿͻ���
//
// ��    �� : 1.0
// ��    �� : Breaker Zhao <breaker.zy_AT_gmail>
// ��    �� : 2010-10
////////////////////////////////////////////////////////////////////////////////

#ifndef __CLIENTVIEW_H__
#define __CLIENTVIEW_H__

////////////////////////////////////////////////////////////////////////////////
// ����ܴ��ڿͻ����� CClientView
////////////////////////////////////////////////////////////////////////////////

class CClientView : public CWnd {
public:
    CClientView() : m_Ellipse(100, 100, 200, 200), m_Color(GRAY_BRUSH) {}
    virtual ~CClientView() {}

private:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = 0);
    virtual void OnDraw(CDC* pDC);

private:
    // ��Ϣ����

    afx_msg void OnPaint();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

    DECLARE_MESSAGE_MAP()

private:
    UINT    m_Color;
    CRect   m_Ellipse;
};

#endif  // __CLIENTVIEW_H__
