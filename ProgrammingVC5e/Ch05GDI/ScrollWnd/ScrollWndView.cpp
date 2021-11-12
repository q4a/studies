// ScrollWndView.cpp : CScrollWndView ���ʵ��
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

// CScrollWndView ����/����

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
    // TODO: �ڴ˴�ͨ���޸�
    //  CREATESTRUCT cs ���޸Ĵ��������ʽ

    return CScrollView::PreCreateWindow(cs);
}

// CScrollWndView ����

void CScrollWndView::OnDraw(CDC* pDC)
{
    // ûʹ�� doc ����
#if 0
    CScrollWndDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;
#endif

    CBrush brushHatch(HS_DIAGCROSS, RGB(255, 0, 0));

    // �豸����, ����Ϳˢԭ��, ������Բ��Ե����ģʽͿˢ������
    CPoint pt(0, 0);
    pDC->LPtoDP(&pt);
    pDC->SetBrushOrg(pt);

    // ���߼����������Բ
    pDC->SelectObject(&brushHatch);
    pDC->Ellipse(&CRect(m_ptTopLeft, m_sizeEllipse));
    pDC->SelectStockObject(BLACK_BRUSH);

    // ���� invalid ����
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
    // SetScaleToFitSize �� CScrollView �� ����Ӧ����ģʽ (stretch-to-fit)
    // ��ʱ�Զ�ʹ�� MM_ANISOTROPIC ӳ��, y ��������, ���ַ�ʽû�й�����, ���Ŵ��ڵĴ�С�ı�, ��ͼ��СҲ��ı�
    SetScaleToFitSize(sizeTotal);
#endif
}


// CScrollWndView ���

#ifdef _DEBUG
void CScrollWndView::AssertValid() const
{
    CScrollView::AssertValid();
}

void CScrollWndView::Dump(CDumpContext& dc) const
{
    CScrollView::Dump(dc);
}

// Debug �汾�� GetDocument()
CScrollWndDoc* CScrollWndView::GetDocument() const
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScrollWndDoc)));
    return (CScrollWndDoc*)m_pDocument;
}
#endif //_DEBUG

// CScrollWndView ��Ϣ�������

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
    // �߼��� rectEllipse
    CRect rectEllipse(m_ptTopLeft, m_sizeEllipse);
    CClientDC dc(this);

    // ���ø��� OnPrepareDC, Ĭ�ϵ� CScrollView::OnPrepareDC ����� SetScrollSizes ��ӳ��ģʽ, �Լ�����λ��, ���ô���ԭ��
    OnPrepareDC(&dc);
    dc.LPtoDP(&rectEllipse);    // �豸�� rectEllipse

    CRgn rgn;
    rgn.CreateEllipticRgnIndirect(&rectEllipse);

    if (rgn.PtInRegion(point)) {
        // ������겶��, �Ӵ��Ժ������������붼�ᵼ�򵽸ô���, ��������ڲ����������֮��
        SetCapture();
        m_bCaptured = TRUE;

        // �豸����� ��Բ top left
        CPoint ptTopLeft(m_ptTopLeft);
        dc.LPtoDP(&ptTopLeft);
        m_sizeOffset = point - ptTopLeft;   // �õ��� rect top left �����е�� size, �豸����

        // TEST: �� rect top left �����е�� rect, ��ͼʹ�õ����߼�����
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
    // ����ƶ�ʱ, ���»�ͼ
    if (m_bCaptured) {
        CClientDC dc(this);
        OnPrepareDC(&dc);

        // ���»�ͼ �� rect, û��ʵ�ʻ���, ֻ�����¼��� update ����
        CRect rectOld(m_ptTopLeft, m_sizeEllipse);
        dc.LPtoDP(rectOld);
        InvalidateRect(rectOld, TRUE);

        // ���� rect top left �߼�����
        m_ptTopLeft = point - m_sizeOffset;
        dc.DPtoLP(&m_ptTopLeft);

        // ���»�ͼ �� rect
        CRect rectNew(m_ptTopLeft, m_sizeEllipse);
        dc.LPtoDP(rectNew);
        InvalidateRect(rectNew, TRUE);
    }
}
