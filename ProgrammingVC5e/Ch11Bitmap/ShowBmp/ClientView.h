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

class CDib;

////////////////////////////////////////////////////////////////////////////////
// ����ܴ��ڿͻ����� CClientView
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
    // ��Ϣ����

    afx_msg void OnPaint();

    DECLARE_MESSAGE_MAP()

private:
    CDib*       m_Dib;
};

#endif  // __CLIENTVIEW_H__
