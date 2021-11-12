// ScrollWndView.h : CScrollWndView ��Ľӿ�
//


#pragma once


class CScrollWndView : public CScrollView {
protected: // �������л�����
    CScrollWndView();
public:
    virtual ~CScrollWndView();

protected:
    DECLARE_DYNCREATE(CScrollWndView)

// ����
public:
    CScrollWndDoc* GetDocument() const;

// ����
public:

// ��д
public:
    virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
    virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

// ���ɵ���Ϣӳ�亯��
protected:
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);

    DECLARE_MESSAGE_MAP()

private:
    const CSize m_sizeEllipse;  // logical
    CPoint m_ptTopLeft; //logical, top left of ellipse rectangle
    CSize m_sizeOffset;    // device, �� rect top left �����е�� size

    BOOL m_bCaptured;
};

#ifndef _DEBUG  // Release �汾�� GetDocument()
inline CScrollWndDoc* CScrollWndView::GetDocument() const
{
    return reinterpret_cast<CScrollWndDoc*>(m_pDocument);
}
#endif
