// DBufScrollView.cpp : implementation of the CDBufScrollView class
//

#include "StdAfx.h"
#include "DBufScroll.h"

#include "DBufScrollDoc.h"
#include "DBufScrollView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDBufScrollView

IMPLEMENT_DYNCREATE(CDBufScrollView, CScrollView)

BEGIN_MESSAGE_MAP(CDBufScrollView, CScrollView)
    ON_WM_PAINT()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CDBufScrollView construction/destruction

CDBufScrollView::CDBufScrollView() :
    m_sizeEllipse(100, 100), m_ptTopLeft(0, 0), m_sizeOffset(0, 0), m_bCaptured(FALSE)
{
    m_pMemDC = new CDC();
    m_pBmp = new CBitmap();
}

CDBufScrollView::~CDBufScrollView()
{
    // NOTE: 注意 delete 顺序
    delete m_pMemDC;    // deselect GDI object
    delete m_pBmp;
}

BOOL CDBufScrollView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs
    return CScrollView::PreCreateWindow(cs);
}

void CDBufScrollView::OnDraw(CDC* pDC)
{
    // 没使用 doc 特性
#if 0
    CDBufScrollDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;
#endif

#define _USE_PAT_BRUSH
#ifdef _USE_PAT_BRUSH
    // 使用 pattern 刷子
    // 设备坐标, 设置涂刷原点, 否则椭圆边缘将和模式涂刷不对齐
    CBrush brush(HS_DIAGCROSS, RGB(255, 0, 0));
    CPoint pt(0, 0);
    pDC->LPtoDP(&pt);
    pDC->SetBrushOrg(pt);
#else
    CBrush brush(RGB(255, 0, 0));
#endif

    // 以逻辑坐标绘制椭圆
    pDC->SelectObject(&brush);
    pDC->Ellipse(&CRect(m_ptTopLeft, m_sizeEllipse));
    pDC->SelectStockObject(BLACK_BRUSH);

    // 测试 invalid 矩形
    pDC->Rectangle(&CRect(100, 100, 200, 200));
}

void CDBufScrollView::OnInitialUpdate()
{
    CScrollView::OnInitialUpdate();

    // NOTE:
    // 如果 DEFAULT_WIDTH 或 DEFAULT_HEIGHT 小于屏幕分辨率, 则当最大化时, 窗口的视口会比看到的小 (客户区一部分)
    // 表现为: 拖动圆形时, 还没到下边, 右边边界就已被遮蔽
    CSize sizeTotal(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    CSize sizePage(sizeTotal.cx/2, sizeTotal.cy/2);
    CSize sizeLine(sizeTotal.cx/50, sizeTotal.cy/50);
    SetScrollSizes(MM_TEXT, sizeTotal, sizePage, sizeLine);

    // 建立 Double Buffer 设施: 内存 DC (m_pMemDC), 缓冲区位图 (m_pBmp)
    if (m_pMemDC->GetSafeHdc() == NULL) {
        CClientDC dc(this);
        OnPrepareDC(&dc);

        // 创建兼容 GDI 位图, 大小和窗口一样大, 包括滚动隐藏部分, 设备坐标
        CRect rectMax(CPoint(0, 0), sizeTotal);
        dc.LPtoDP(&rectMax);
        m_pBmp->CreateCompatibleBitmap(&dc, rectMax.right, rectMax.bottom);

        m_pMemDC->CreateCompatibleDC(&dc);
        m_pMemDC->SetMapMode(MM_TEXT);
    }
}

// CDBufScrollView diagnostics
#ifdef _DEBUG
void CDBufScrollView::AssertValid() const
{
    CScrollView::AssertValid();
}
void CDBufScrollView::Dump(CDumpContext& dc) const
{
    CScrollView::Dump(dc);
}
CDBufScrollDoc* CDBufScrollView::GetDocument() const // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDBufScrollDoc)));
    return (CDBufScrollDoc*) m_pDocument;
}
#endif  //_DEBUG

void CDBufScrollView::OnPaint()
{
    // NOTE:
    // CView::OnPaint 的默认行为是:
    // 1. CPaintDC dc(this)
    // 2. OnPrepareDC(&dc)
    // 3. OnDraw(&dc)
    // OnPrint 也以相似的方式调用 OnDraw, 即:
    // OnPaint 控制显示器的绘图, OnPrint 控制打印机的绘图, 而 OnDraw 是显示器 与 打印机 绘图的公共部分
    // 双缓冲机制对打印绘图是没有意义, 所以将双缓冲代码放到 OnPaint 中, 而不是公共的 OnDraw 中

    CPaintDC dc(this);
    OnPrepareDC(&dc);

    ASSERT(m_pMemDC != NULL);
    ASSERT(m_pBmp != NULL);

    // NOTE: Double Buffer 流程

    // 设置剪裁区域 或者称 update rect
    CRect rectClip;
    dc.GetClipBox(&rectClip);
    m_pMemDC->SelectClipRgn(NULL);
    m_pMemDC->IntersectClipRect(&rectClip);

    // 填充内存 dc 的背景 (仅在剪裁区域内)
    CBitmap* pOldBmp = m_pMemDC->SelectObject(m_pBmp);
    CBrush bgBrush(::GetSysColor(COLOR_WINDOW));
    CBrush* pOldBrush = m_pMemDC->SelectObject(&bgBrush);
    m_pMemDC->PatBlt(rectClip.left, rectClip.top, rectClip.Width(), rectClip.Height(), PATCOPY);

    // NOTE:
    // 采用非 MM_TEXT 模式时, 图形的拉伸, 鼠标消息中的绘图 和 这里的 PatBlt
    // 会导致图形边缘部分有时不会被完整的用背景色擦除, 会留下边框线, 解决方法
    // 1. 设置活动 pen 为背景色, 这样在画图形时, 边框便不会显现
    // 2. 使用 MM_TEXT 映射模式
#ifdef _ERASE_BORDER
    CPen pen(PS_SOLID, 0, ::GetSysColor(COLOR_WINDOW));
    CPen* pOldPen = m_pMemDC->SelectObject(&pen);
    m_pMemDC->Rectangle(&rectClip);
    m_pMemDC->SelectObject(pOldPen);
#endif

    // 在内存 DC 中绘图, 完毕后 blit 到设备 DC 中
    OnDraw(m_pMemDC);
    dc.BitBlt(rectClip.left, rectClip.top, rectClip.Width(), rectClip.Height(), m_pMemDC, rectClip.left, rectClip.top, SRCCOPY);

    // 恢复 GDI 对象
    m_pMemDC->SelectObject(pOldBrush);
    m_pMemDC->SelectObject(pOldBmp);
}

void CDBufScrollView::OnLButtonDown(UINT nFlags, CPoint point)
{
    CRect rectEllipse(m_ptTopLeft, m_sizeEllipse);
    CRgn circle;

    CClientDC dc(this);
    OnPrepareDC(&dc);
    dc.LPtoDP(&rectEllipse);
    circle.CreateEllipticRgnIndirect(rectEllipse);

    if (circle.PtInRegion(point)) {
        SetCapture();
        m_bCaptured = TRUE;
        CPoint ptTopLeft(m_ptTopLeft);
        dc.LPtoDP(&ptTopLeft);
        m_sizeOffset = point - ptTopLeft;
        ::SetCursor(::LoadCursor(NULL, IDC_CROSS));
    }
}

void CDBufScrollView::OnLButtonUp(UINT nFlags, CPoint point)
{
    if (m_bCaptured) {
        ::ReleaseCapture();
        m_bCaptured = FALSE;
    }
}

void CDBufScrollView::OnMouseMove(UINT nFlags, CPoint point)
{
    if (m_bCaptured) {
        CClientDC dc(this);
        OnPrepareDC(&dc);

        CRect rectOld(m_ptTopLeft, m_sizeEllipse);
        dc.LPtoDP(&rectOld);
        InvalidateRect(rectOld, FALSE); // 设为 FALSE, Windows 不做背景擦除, 或者说由用户负责背景擦除
        m_ptTopLeft = point - m_sizeOffset;
        dc.DPtoLP(&m_ptTopLeft);

        CRect rectNew(m_ptTopLeft, m_sizeEllipse);
        dc.LPtoDP(&rectNew);
        InvalidateRect(rectNew, FALSE);
    }
}
