// BmpResView.cpp : implementation of the CBmpResView class
//

#include "StdAfx.h"
#include "BmpRes.h"

#include "BmpResDoc.h"
#include "BmpResView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CBmpResView

IMPLEMENT_DYNCREATE(CBmpResView, CView)

BEGIN_MESSAGE_MAP(CBmpResView, CView)
END_MESSAGE_MAP()

// CBmpResView construction/destruction

CBmpResView::CBmpResView()
{
}

CBmpResView::~CBmpResView()
{
}

BOOL CBmpResView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs
    return CView::PreCreateWindow(cs);
}

// CBmpResView drawing

void CBmpResView::OnDraw(CDC* pDC)
{
    CBmpResDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    // NOTE:
    // 在释放 GDI 对象资源前, 要保证没有被选进 DC, 即从 DC 中选出该 GDI 对象, CDC 对象析构时会完成选出动作
    // 用 GDI 类 (CGdiObject, CBitmap, CBrush...) 的 DeleteObject() 可以释放 GDI 资源, GDI 类对象析构, 也能释放 GDI 对象
    // 所以 CBitmap bmp; CDC dcMem; 的定义顺序很重要: 先是 bmp, 后是 dcMem, 这样保证先析构 dcMem (从 DC 选出 GDI 位图), 后析构 bmp (删除 GDI 位图)
    CBitmap bmp;    // 1
    CDC dcMem;      // 2
    bmp.LoadBitmap(IDB_BMP01);
    dcMem.CreateCompatibleDC(pDC);
    dcMem.SelectObject(&bmp);
    pDC->BitBlt(50, 50, 256, 512, &dcMem, 0, 0, SRCCOPY);
}

// CBmpResView diagnostics
#ifdef _DEBUG
void CBmpResView::AssertValid() const
{
    CView::AssertValid();
}

void CBmpResView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CBmpResDoc* CBmpResView::GetDocument() const // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBmpResDoc)));
    return (CBmpResDoc*) m_pDocument;
}
#endif //_DEBUG
