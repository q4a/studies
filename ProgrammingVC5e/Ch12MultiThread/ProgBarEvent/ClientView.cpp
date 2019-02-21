////////////////////////////////////////////////////////////////////////////////
// 文    件 : ClientView.cpp
// 功能说明 :
//   主框架窗口客户区
//
// 版    本 : 1.0
// 作    者 : Breaker Zhao <breaker.zy_AT_gmail>
// 日    期 : 2010-10
////////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "ProgBarEvent.h"
#include "ClientView.h"

////////////////////////////////////////////////////////////////////////////////
// 主框架窗口客户区类 CClientView
////////////////////////////////////////////////////////////////////////////////

// 消息映射
BEGIN_MESSAGE_MAP(CClientView, CWnd)
    ON_WM_PAINT()
    ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

BOOL CClientView::PreCreateWindow(CREATESTRUCT& cs)
{
    if (!CWnd::PreCreateWindow(cs))
        return FALSE;

    cs.dwExStyle |= WS_EX_CLIENTEDGE;   // 增加下沉边框样式 (sunken edge)
    cs.style &= ~WS_BORDER;             // 去掉边框
    cs.lpszClass = AfxRegisterWndClass(0, LoadCursor(0, IDC_ARROW), (HBRUSH) (COLOR_WINDOW + 1), 0);
    return TRUE;
}

void CClientView::OnPaint()
{
    // NOTE: 不要调用父类 CWnd::OnPaint 绘图
    CPaintDC dc(this);
    OnPrepareDC(&dc);
    OnDraw(&dc);
}

void CClientView::OnDraw(CDC* pDC)
{
    ASSERT_VALID(pDC);
    pDC->SelectStockObject(m_Color);
    pDC->Ellipse(&m_Ellipse);
}

void CClientView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo/* = 0*/)
{
    // NOTE: 在 OnPrepareDC 中设定映射方式和坐标原点
    pDC->SetMapMode(MM_TEXT);
}

void CClientView::OnLButtonDown(UINT nFlags, CPoint point)
{
    CClientDC dc(this);
    OnPrepareDC(&dc);
    CRect rect(m_Ellipse);
    // 转换成设备坐标才能判断点击位置, 因为 point 是设备坐标
    dc.LPtoDP(&rect);

    CRgn rgn;
    rgn.CreateEllipticRgnIndirect(&rect);
    // 如果鼠标点击位置在椭圆内部, 则变换颜色
    if (rgn.PtInRegion(point))
        m_Color = (m_Color == GRAY_BRUSH ? WHITE_BRUSH : GRAY_BRUSH);
    // 使椭圆外接矩形无效, 只重绘这部分区域
    InvalidateRect(rect);
}
