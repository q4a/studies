// FontLogicalTWIPView.cpp : implementation of the CFontLogicalTWIPView class
//

#include "StdAfx.h"
#include "FontLogicalTWIP.h"

#include "FontLogicalTWIPDoc.h"
#include "FontLogicalTWIPView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CFontLogicalTWIPView

IMPLEMENT_DYNCREATE(CFontLogicalTWIPView, CView)

BEGIN_MESSAGE_MAP(CFontLogicalTWIPView, CView)
END_MESSAGE_MAP()

// CFontLogicalTWIPView construction/destruction

CFontLogicalTWIPView::CFontLogicalTWIPView()
{
    // TODO: add construction code here

}

CFontLogicalTWIPView::~CFontLogicalTWIPView()
{
}

BOOL CFontLogicalTWIPView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs

    return CView::PreCreateWindow(cs);
}

// CFontLogicalTWIPView drawing

void CFontLogicalTWIPView::OnDraw(CDC* pDC)
{
#if 0
    CFontLogicalTWIPDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;
#endif

    int nPos = 0;
    for (int i = 6; i <= 24; i+=2)
        ShowFont(pDC, nPos, i);

    // 分辨率 单位 dpi
    TRACE("LOGPIXELSX: %d, LOGPIXELSY: %d\n", pDC->GetDeviceCaps(LOGPIXELSX), pDC->GetDeviceCaps(LOGPIXELSY));

    // 显示器的物理尺寸 单位 毫米
    TRACE("HORZSIZE: %d, VERTSIZE: %d\n", pDC->GetDeviceCaps(HORZSIZE), pDC->GetDeviceCaps(VERTSIZE));

    // 显示器的逻辑尺寸 单位 像素, 乘以 LOGPIXELSX 和 LOGPIXELSY 后得到英寸为单位的逻辑尺寸
    TRACE("HORZRES: %d, VERTRES: %d\n", pDC->GetDeviceCaps(HORZRES), pDC->GetDeviceCaps(VERTRES));
}

// CFontLogicalTWIPView diagnostics

#ifdef _DEBUG
void CFontLogicalTWIPView::AssertValid() const
{
    CView::AssertValid();
}

void CFontLogicalTWIPView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CFontLogicalTWIPDoc* CFontLogicalTWIPView::GetDocument() const // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFontLogicalTWIPDoc)));
    return (CFontLogicalTWIPDoc*)m_pDocument;
}
#endif //_DEBUG

void CFontLogicalTWIPView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
    // 逻辑 TWIP 映射的设置方法，这种映射与显示分辨率无关
    // 1 TWIP单位 = 1/20 磅, 1 磅 = 1/72 英寸, 1 TWIP 单位 = 1/1440 英寸
    // 下面按 1 TWIP 单位 映射 分辨率数值

    pDC->SetMapMode(MM_ANISOTROPIC);
    pDC->SetWindowExt(1440, 1440);
    pDC->SetViewportExt(pDC->GetDeviceCaps(LOGPIXELSX), -pDC->GetDeviceCaps(LOGPIXELSY));
}

void CFontLogicalTWIPView::ShowFont(CDC* pDC, IN OUT int& nPos, int nPoints)
{
    TEXTMETRIC tm;
    CFont font;
    CString strText;
    CSize sizeText;

    // CreateFont() 中，如果字符高度为负，表示指定的是 tmHeight - tmInternalLeading (净高)
    // 如果字符高度为正值，表示指定的是 tmHeight，此时字体会小一些
    font.CreateFont(-nPoints * 20, 0, 0, 0, 400, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));
    CFont* pOldFont = (CFont*) pDC->SelectObject(&font);

    pDC->GetTextMetrics(&tm);
    TRACE("points = %d, tmHeight = %d, tmInternalLeading = %d, tmExternalLeading = %d\n",
          nPoints, tm.tmHeight, tm.tmInternalLeading, tm.tmExternalLeading);

    strText.Format(_T("This is %d-point Arial"), nPoints);
    // GetTextExtent() 取得字符的高度是不包括 tmExternalLeading 的 tmHeight，即字体高度
    sizeText = pDC->GetTextExtent(strText);
    TRACE("string width = %d, string height = %d\n", sizeText.cx, sizeText.cy);

    pDC->TextOut(0, nPos, strText);
    pDC->SelectObject(pOldFont);
    nPos -= tm.tmHeight + tm.tmExternalLeading;
}


