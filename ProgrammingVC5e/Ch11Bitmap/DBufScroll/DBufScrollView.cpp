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
    // NOTE: ע�� delete ˳��
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
    // ûʹ�� doc ����
#if 0
    CDBufScrollDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;
#endif

#define _USE_PAT_BRUSH
#ifdef _USE_PAT_BRUSH
    // ʹ�� pattern ˢ��
    // �豸����, ����Ϳˢԭ��, ������Բ��Ե����ģʽͿˢ������
    CBrush brush(HS_DIAGCROSS, RGB(255, 0, 0));
    CPoint pt(0, 0);
    pDC->LPtoDP(&pt);
    pDC->SetBrushOrg(pt);
#else
    CBrush brush(RGB(255, 0, 0));
#endif

    // ���߼����������Բ
    pDC->SelectObject(&brush);
    pDC->Ellipse(&CRect(m_ptTopLeft, m_sizeEllipse));
    pDC->SelectStockObject(BLACK_BRUSH);

    // ���� invalid ����
    pDC->Rectangle(&CRect(100, 100, 200, 200));
}

void CDBufScrollView::OnInitialUpdate()
{
    CScrollView::OnInitialUpdate();

    // NOTE:
    // ��� DEFAULT_WIDTH �� DEFAULT_HEIGHT С����Ļ�ֱ���, �����ʱ, ���ڵ��ӿڻ�ȿ�����С (�ͻ���һ����)
    // ����Ϊ: �϶�Բ��ʱ, ��û���±�, �ұ߽߱���ѱ��ڱ�
    CSize sizeTotal(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    CSize sizePage(sizeTotal.cx/2, sizeTotal.cy/2);
    CSize sizeLine(sizeTotal.cx/50, sizeTotal.cy/50);
    SetScrollSizes(MM_TEXT, sizeTotal, sizePage, sizeLine);

    // ���� Double Buffer ��ʩ: �ڴ� DC (m_pMemDC), ������λͼ (m_pBmp)
    if (m_pMemDC->GetSafeHdc() == NULL) {
        CClientDC dc(this);
        OnPrepareDC(&dc);

        // �������� GDI λͼ, ��С�ʹ���һ����, �����������ز���, �豸����
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
    // CView::OnPaint ��Ĭ����Ϊ��:
    // 1. CPaintDC dc(this)
    // 2. OnPrepareDC(&dc)
    // 3. OnDraw(&dc)
    // OnPrint Ҳ�����Ƶķ�ʽ���� OnDraw, ��:
    // OnPaint ������ʾ���Ļ�ͼ, OnPrint ���ƴ�ӡ���Ļ�ͼ, �� OnDraw ����ʾ�� �� ��ӡ�� ��ͼ�Ĺ�������
    // ˫������ƶԴ�ӡ��ͼ��û������, ���Խ�˫�������ŵ� OnPaint ��, �����ǹ����� OnDraw ��

    CPaintDC dc(this);
    OnPrepareDC(&dc);

    ASSERT(m_pMemDC != NULL);
    ASSERT(m_pBmp != NULL);

    // NOTE: Double Buffer ����

    // ���ü������� ���߳� update rect
    CRect rectClip;
    dc.GetClipBox(&rectClip);
    m_pMemDC->SelectClipRgn(NULL);
    m_pMemDC->IntersectClipRect(&rectClip);

    // ����ڴ� dc �ı��� (���ڼ���������)
    CBitmap* pOldBmp = m_pMemDC->SelectObject(m_pBmp);
    CBrush bgBrush(::GetSysColor(COLOR_WINDOW));
    CBrush* pOldBrush = m_pMemDC->SelectObject(&bgBrush);
    m_pMemDC->PatBlt(rectClip.left, rectClip.top, rectClip.Width(), rectClip.Height(), PATCOPY);

    // NOTE:
    // ���÷� MM_TEXT ģʽʱ, ͼ�ε�����, �����Ϣ�еĻ�ͼ �� ����� PatBlt
    // �ᵼ��ͼ�α�Ե������ʱ���ᱻ�������ñ���ɫ����, �����±߿���, �������
    // 1. ���û pen Ϊ����ɫ, �����ڻ�ͼ��ʱ, �߿�㲻������
    // 2. ʹ�� MM_TEXT ӳ��ģʽ
#ifdef _ERASE_BORDER
    CPen pen(PS_SOLID, 0, ::GetSysColor(COLOR_WINDOW));
    CPen* pOldPen = m_pMemDC->SelectObject(&pen);
    m_pMemDC->Rectangle(&rectClip);
    m_pMemDC->SelectObject(pOldPen);
#endif

    // ���ڴ� DC �л�ͼ, ��Ϻ� blit ���豸 DC ��
    OnDraw(m_pMemDC);
    dc.BitBlt(rectClip.left, rectClip.top, rectClip.Width(), rectClip.Height(), m_pMemDC, rectClip.left, rectClip.top, SRCCOPY);

    // �ָ� GDI ����
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
        InvalidateRect(rectOld, FALSE); // ��Ϊ FALSE, Windows ������������, ����˵���û����𱳾�����
        m_ptTopLeft = point - m_sizeOffset;
        dc.DPtoLP(&m_ptTopLeft);

        CRect rectNew(m_ptTopLeft, m_sizeEllipse);
        dc.LPtoDP(&rectNew);
        InvalidateRect(rectNew, FALSE);
    }
}
