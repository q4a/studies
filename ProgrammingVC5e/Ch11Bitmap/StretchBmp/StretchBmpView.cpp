// StretchBmpView.cpp : implementation of the CStretchBmpView class
//

#include "StdAfx.h"
#include "StretchBmp.h"

#include "StretchBmpDoc.h"
#include "StretchBmpView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CStretchBmpView

IMPLEMENT_DYNCREATE(CStretchBmpView, CScrollView)

BEGIN_MESSAGE_MAP(CStretchBmpView, CScrollView)
    // Standard printing commands
    ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CStretchBmpView construction/destruction

CStretchBmpView::CStretchBmpView() :
    m_sizeSrc(0, 0), m_sizeDest(0, 0)
{
    m_pMemDC = new CDC();
    m_pBmp = new CBitmap();
}

CStretchBmpView::~CStretchBmpView()
{
    delete m_pMemDC;
    delete m_pBmp;
}

BOOL CStretchBmpView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs
    return CScrollView::PreCreateWindow(cs);
}

void CStretchBmpView::OnDraw(CDC* pDC)
{
    // 没使用 doc 特性
#if 0
    CStretchBmpDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;
#endif

    // SetStretchBltMode 可以让缩小的位图好看些
    pDC->SetStretchBltMode(COLORONCOLOR);

    // StretchBlt 的 dest, src 均使用相关 dc 的逻辑坐标
    // m_pMemDC 一直使用默认的 MM_TEXT 设备坐标系, CreateCompatibleDC 并不从相关 dc 中拷贝映射的设置
    // TRACE1("**** 1 m_pMemDC->GetMapMode(): %d\n", m_pMemDC->GetMapMode());
    // TRACE1("**** 2 pDC->GetMapMode(): %d\n", pDC->GetMapMode());

    // 使用计算后的逻辑坐标
    pDC->StretchBlt(20, -20, m_sizeDest.cx, -m_sizeDest.cy, m_pMemDC, 0, 0, m_sizeSrc.cx, m_sizeSrc.cy, SRCCOPY);

    // 每个像素映射为 MM_LOENGLISH 单位的方块
    pDC->StretchBlt(400, -20, m_sizeSrc.cx, -m_sizeSrc.cy, m_pMemDC, 0, 0, m_sizeSrc.cx, m_sizeSrc.cy, SRCCOPY);
}

void CStretchBmpView::OnInitialUpdate()
{
    CScrollView::OnInitialUpdate();

    CSize sizeTotal(800, 1050);
    CSize sizeLine = CSize(sizeTotal.cx/100, sizeTotal.cy/100);
    SetScrollSizes(MM_LOENGLISH, sizeTotal, sizeTotal, sizeLine);
    BITMAP bm;

    if (m_pMemDC->GetSafeHdc() == NULL) {
        CClientDC dc(this);
        // TRACE1("**** 1 dc.GetMapMode(): %d\n", dc.GetMapMode());

        // 在 OnPrepareDC 中设置 dc 的映射模式, 新建的 dc 的映射模式为 MM_TEXT
        // 默认的 OnPaint 会调用 OnPrepareDC
        // 如果调用了 SetScrollSizes, 则默认的 OnPrepareDC 会将 dc 设置成相同的映射模式
        OnPrepareDC(&dc);
        // TRACE1("**** 2 dc.GetMapMode(): %d\n", dc.GetMapMode());

        m_pBmp->LoadBitmap(IDB_BITMAP1);
        m_pBmp->GetObject(sizeof(bm), &bm);

        m_sizeSrc.cx = bm.bmWidth;
        m_sizeSrc.cy = bm.bmHeight;

        // m_pMemDC 一直使用默认的 MM_TEXT 设备坐标系, CreateCompatibleDC() 并不从相关 dc 中拷贝映射的设置
        m_pMemDC->CreateCompatibleDC(&dc);
        m_pMemDC->SelectObject(m_pBmp);
        m_sizeDest = m_sizeSrc;
        dc.DPtoLP(&m_sizeDest);
    }
}


// CStretchBmpView printing

BOOL CStretchBmpView::OnPreparePrinting(CPrintInfo* pInfo)
{
    // default preparation
    return DoPreparePrinting(pInfo);
}

void CStretchBmpView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add extra initialization before printing
}

void CStretchBmpView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add cleanup after printing
}


// CStretchBmpView diagnostics

#ifdef _DEBUG
void CStretchBmpView::AssertValid() const
{
    CScrollView::AssertValid();
}

void CStretchBmpView::Dump(CDumpContext& dc) const
{
    CScrollView::Dump(dc);
}

CStretchBmpDoc* CStretchBmpView::GetDocument() const // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStretchBmpDoc)));
    return (CStretchBmpDoc*) m_pDocument;
}
#endif //_DEBUG
