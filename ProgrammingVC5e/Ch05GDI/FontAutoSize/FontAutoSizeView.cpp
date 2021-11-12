// FontAutoSizeView.cpp : implementation of the CFontAutoSizeView class
//

#include "StdAfx.h"
#include "FontAutoSize.h"

#include "FontAutoSizeDoc.h"
#include "FontAutoSizeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFontAutoSizeView

IMPLEMENT_DYNCREATE(CFontAutoSizeView, CView)

BEGIN_MESSAGE_MAP(CFontAutoSizeView, CView)
END_MESSAGE_MAP()

// CFontAutoSizeView construction/destruction

CFontAutoSizeView::CFontAutoSizeView()
{
    // TODO: add construction code here

}

CFontAutoSizeView::~CFontAutoSizeView()
{
}

BOOL CFontAutoSizeView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs

    return CView::PreCreateWindow(cs);
}

// CFontAutoSizeView drawing

void CFontAutoSizeView::OnDraw(CDC* pDC)
{
#if 0
    CFontAutoSizeDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;
#endif

    CFont font_1, font_2, font_3, font_4;

    // TrueType 字体 Arial
    font_1.CreateFont(50, 0, 0, 0, 400, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));
    CFont* pOldFont = (CFont*) pDC->SelectObject(&font_1);
    TraceMetrics(pDC);
    pDC->TextOut(0, 0, _T("This is Arial, default width"));

    // 非 TrueType 字体 Courier
    // Courier 这种光栅字体，缩小到一定程度后就不能在缩小，放大到一定程度后有锯齿
    font_2.CreateFont(50, 0, 0, 0, 400, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("Courier"));
    pDC->SelectObject(&font_2);
    TraceMetrics(pDC);
    pDC->TextOut(0, 100, _T("This is Courier, default width"));

    // 根据 字体高, 宽 自动选择 FF_ROMAN 字体
    // 自动选择了 Times New Roman (TrueType) 字体
    // 因为这里设定了字体宽度 10，所以在改变窗口宽度时，font_3 字体的宽度总会改变以适应窗口
    font_3.CreateFont(50, 10, 0, 0, 400, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, NULL);
    pDC->SelectObject(&font_3);
    TraceMetrics(pDC);
    pDC->TextOut(0, 200, _T("This is generic Roman, variable width"));

    // 非显示器字体 LinePrinter
    // 字体发生器根据指定的 FF_MODERN 选择了 Courier New (TrueType) 字体
    font_4.CreateFont(50, 0, 0, 0, 400, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("LinePrinter"));
    pDC->SelectObject(&font_4);
    TraceMetrics(pDC);
    pDC->TextOut(0, 300, _T("This is LinePrinter, default width"));

    pDC->SelectObject(pOldFont);
}

// CFontAutoSizeView diagnostics

#ifdef _DEBUG
void CFontAutoSizeView::AssertValid() const
{
    CView::AssertValid();
}

void CFontAutoSizeView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CFontAutoSizeDoc* CFontAutoSizeView::GetDocument() const // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFontAutoSizeDoc)));
    return (CFontAutoSizeDoc*)m_pDocument;
}
#endif //_DEBUG

// CFontAutoSizeView message handlers

void CFontAutoSizeView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
    CRect clientRect;
    GetClientRect(&clientRect);

    pDC->SetMapMode(MM_ANISOTROPIC);    // +y = down
    pDC->SetWindowExt(1280, 800);
    pDC->SetViewportExt(clientRect.right, clientRect.bottom);
    pDC->SetViewportOrg(0, 0);
}

void CFontAutoSizeView::TraceMetrics(CDC* pDC)
{
    TEXTMETRIC tm;
    CString strFaceName;

    pDC->GetTextMetrics(&tm);
    // 取得字体名
    pDC->GetTextFace(strFaceName);

    TRACE(_T("font: %s, tmHeight: %d, tmInternalLeading: %d, tmExternalLeading: %d\n"),
          strFaceName, tm.tmHeight, tm.tmInternalLeading, tm.tmExternalLeading);
}
