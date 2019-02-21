// ScrollWndView.h : CScrollWndView 类的接口
//


#pragma once


class CScrollWndView : public CScrollView {
protected: // 仅从序列化创建
    CScrollWndView();
public:
    virtual ~CScrollWndView();

protected:
    DECLARE_DYNCREATE(CScrollWndView)

// 属性
public:
    CScrollWndDoc* GetDocument() const;

// 操作
public:

// 重写
public:
    virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
    virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

// 生成的消息映射函数
protected:
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);

    DECLARE_MESSAGE_MAP()

private:
    const CSize m_sizeEllipse;  // logical
    CPoint m_ptTopLeft; //logical, top left of ellipse rectangle
    CSize m_sizeOffset;    // device, 从 rect top left 到击中点的 size

    BOOL m_bCaptured;
};

#ifndef _DEBUG  // Release 版本的 GetDocument()
inline CScrollWndDoc* CScrollWndView::GetDocument() const
{
    return reinterpret_cast<CScrollWndDoc*>(m_pDocument);
}
#endif
