// ScrollWndView.cpp : CScrollWndView 类的实现
//

#include "StdAfx.h"
#include "ScrollWnd.h"

#include "ScrollWndDoc.h"
#include "ScrollWndView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CScrollWndView

IMPLEMENT_DYNCREATE(CScrollWndView, CScrollView)

BEGIN_MESSAGE_MAP(CScrollWndView, CScrollView)
    ON_WM_KEYDOWN()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CScrollWndView 构造/析构

CScrollWndView::CScrollWndView() :
    m_sizeEllipse(100, 100),
    m_ptTopLeft(0, 0),
    m_sizeOffset(0, 0),
    m_bCaptured(FALSE)
{
}

CScrollWndView::~CScrollWndView()
{
}

BOOL CScrollWndView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: 在此处通过修改
    //  CREATESTRUCT cs 来修改窗口类或样式

    return CScrollView::PreCreateWindow(cs);
}

// CScrollWndView 绘制

void CScrollWndView::OnDraw(CDC* pDC)
{
    // 没使用 doc 特性
#if 0
    CScrollWndDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;
#endif

    CBrush brushHatch(HS_DIAGCROSS, RGB(255, 0, 0));

    // 设备坐标, 设置涂刷原点, 否则椭圆边缘将和模式涂刷不对齐
    CPoint pt(0, 0);
    pDC->LPtoDP(&pt);
    pDC->SetBrushOrg(pt);

    // 以逻辑坐标绘制椭圆
    pDC->SelectObject(&brushHatch);
    pDC->Ellipse(&CRect(m_ptTopLeft, m_sizeEllipse));
    pDC->SelectStockObject(BLACK_BRUSH);

    // 测试 invalid 矩形
    pDC->Rectangle(&CRect(100, 100, 200, 200));
}

void CScrollWndView::OnInitialUpdate()
{
    CScrollView::OnInitialUpdate();

    CSize sizeTotal(800, 600);
    CSize sizePage(sizeTotal.cx/2, sizeTotal.cy/2);
    CSize sizeLine(sizeTotal.cx/50, sizeTotal.cy/50);

//#define _STRETCH_TO_FIT
#ifndef _STRETCH_TO_FIT
    SetScrollSizes(MM_TEXT, sizeTotal, sizePage, sizeLine);
#else
    // SetScaleToFitSize 是 CScrollView 的 自适应伸缩模式 (stretch-to-fit)
    // 此时自动使用 MM_ANISOTROPIC 映射, y 向下增加, 这种方式没有滚动条, 随着窗口的大小改变, 绘图大小也会改变
    SetScaleToFitSize(sizeTotal);
#endif
}


// CScrollWndView 诊断

#ifdef _DEBUG
void CScrollWndView::AssertValid() const
{
    CScrollView::AssertValid();
}

void CScrollWndView::Dump(CDumpContext& dc) const
{
    CScrollView::Dump(dc);
}

// Debug 版本的 GetDocument()
CScrollWndDoc* CScrollWndView::GetDocument() const
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScrollWndDoc)));
    return (CScrollWndDoc*)m_pDocument;
}
#endif //_DEBUG

// CScrollWndView 消息处理程序

void CScrollWndView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    switch (nChar) {
    case VK_HOME:
        OnVScroll(SB_TOP, 0, NULL);
        OnHScroll(SB_LEFT, 0, NULL);
        break;

    case VK_END:
        OnVScroll(SB_BOTTOM, 0, NULL);
        OnHScroll(SB_RIGHT, 0, NULL);
        break;

    case VK_UP:
        OnVScroll(SB_LINEUP, 0, NULL);
        break;

    case VK_DOWN:
        OnVScroll(SB_LINEDOWN, 0, NULL);
        break;

    case VK_PRIOR:
        OnVScroll(SB_PAGEUP, 0, NULL);
        break;

    case VK_NEXT:
        OnVScroll(SB_PAGEDOWN, 0, NULL);
        break;

    case VK_LEFT:
        OnHScroll(SB_LINELEFT, 0, NULL);
        break;

    case VK_RIGHT:
        OnHScroll(SB_LINERIGHT, 0, NULL);
        break;

    default:
        break;
    }
}

void CScrollWndView::OnLButtonDown(UINT nFlags, CPoint point)
{
    // 逻辑的 rectEllipse
    CRect rectEllipse(m_ptTopLeft, m_sizeEllipse);
    CClientDC dc(this);

    // 不用覆盖 OnPrepareDC, 默认的 CScrollView::OnPrepareDC 会根据 SetScrollSizes 的映射模式, 以及滚动位置, 设置窗口原点
    OnPrepareDC(&dc);
    dc.LPtoDP(&rectEllipse);    // 设备的 rectEllipse

    CRgn rgn;
    rgn.CreateEllipticRgnIndirect(&rectEllipse);

    if (rgn.PtInRegion(point)) {
        // 设置鼠标捕获, 从此以后鼠标的所有输入都会导向到该窗口, 不管鼠标在不在这个窗口之上
        SetCapture();
        m_bCaptured = TRUE;

        // 设备坐标的 椭圆 top left
        CPoint ptTopLeft(m_ptTopLeft);
        dc.LPtoDP(&ptTopLeft);
        m_sizeOffset = point - ptTopLeft;   // 得到从 rect top left 到击中点的 size, 设备坐标

        // TEST: 从 rect top left 到击中点的 rect, 绘图使用的是逻辑坐标
        //CRect r1(ptTopLeft, m_sizeOffset);
        //dc.DPtoLP(&r1);
        //CBrush brush(RGB(255, 0, 255));
        //dc.SelectObject(&brush);
        //dc.Rectangle(&r1);
        //dc.SelectStockObject(BLACK_BRUSH);

        ::SetCursor(::LoadCursor(NULL, IDC_CROSS));
    }
}

void CScrollWndView::OnLButtonUp(UINT nFlags, CPoint point)
{
    if (m_bCaptured) {
        ::ReleaseCapture();
        m_bCaptured = FALSE;
    }
}

void CScrollWndView::OnMouseMove(UINT nFlags, CPoint point)
{
    // 鼠标移动时, 更新绘图
    if (m_bCaptured) {
        CClientDC dc(this);
        OnPrepareDC(&dc);

        // 更新绘图 旧 rect, 没有实际绘制, 只是重新计算 update 区域
        CRect rectOld(m_ptTopLeft, m_sizeEllipse);
        dc.LPtoDP(rectOld);
        InvalidateRect(rectOld, TRUE);

        // 更新 rect top left 逻辑坐标
        m_ptTopLeft = point - m_sizeOffset;
        dc.DPtoLP(&m_ptTopLeft);

        // 更新绘图 新 rect
        CRect rectNew(m_ptTopLeft, m_sizeEllipse);
        dc.LPtoDP(rectNew);
        InvalidateRect(rectNew, TRUE);
    }
}
