// HexView.cpp : implementation of the CHexView class
//

#include "StdAfx.h"
#include "PoemSwitch.h"

#include "PoemDoc.h"
#include "HexView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHexView

IMPLEMENT_DYNCREATE(CHexView, CScrollView)

BEGIN_MESSAGE_MAP(CHexView, CScrollView)
    // Standard printing commands
    ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CHexView construction/destruction

CHexView::CHexView() : m_RectPrint(0, 0, 11520, -15120)
{
}

CHexView::~CHexView()
{
}

BOOL CHexView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs

    return CScrollView::PreCreateWindow(cs);
}

// CHexView drawing

void CHexView::OnDraw(CDC* pDC)
{
    int i, j, k, l, n, height;
    CString line, str;
    CFont font;
    TEXTMETRIC tm;

    CPoemDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    // print the poem in hex
    font.CreateFont(-160, 80, 0, 0, 400, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));
    CFont* oldFont = (CFont*) pDC->SelectObject(&font);
    pDC->GetTextMetrics(&tm);
    height = tm.tmHeight + tm.tmExternalLeading;
    MYTRACE("font height = %d, internal leading = %d", height, tm.tmInternalLeading);
    j = (int) pDoc->m_StringArray.GetSize();
    for (i = 0; i < j; ++i) {
        line.Format(_T("%02x  "), i);
        l = pDoc->m_StringArray[i].GetLength();
        for (k = 0; k < l; ++k) {
            n = pDoc->m_StringArray[i][k] & 0xff;
            str.Format(_T("%02x "), n);
            line += str;
        }
        pDC->TextOut(720, -i * height - 720, line);
    }

    pDC->SelectObject(oldFont);
    MYTRACE("LOGPIXELSX = %d, LOGPIXELSY = %d", pDC->GetDeviceCaps(LOGPIXELSX), pDC->GetDeviceCaps(LOGPIXELSY));
    MYTRACE("HORZSIZE = %d, VERTSIZE = %d", pDC->GetDeviceCaps(HORZSIZE), pDC->GetDeviceCaps(VERTSIZE));
}

void CHexView::OnInitialUpdate()
{
    CScrollView::OnInitialUpdate();

    CSize sizeTotal(m_RectPrint.Width(), -m_RectPrint.Height());
    CSize sizePage(sizeTotal.cx / 2, sizeTotal.cy / 2);
    CSize sizeLine(sizeTotal.cx / 100, sizeTotal.cy / 100);
    SetScrollSizes(MM_TWIPS, sizeTotal, sizePage, sizeLine);
}


// CHexView printing

BOOL CHexView::OnPreparePrinting(CPrintInfo* pInfo)
{
    pInfo->SetMaxPage(1);
    return DoPreparePrinting(pInfo);
}

void CHexView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add extra initialization before printing
}

void CHexView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add cleanup after printing
}


// CHexView diagnostics

#ifdef _DEBUG
void CHexView::AssertValid() const
{
    CScrollView::AssertValid();
}

void CHexView::Dump(CDumpContext& dc) const
{
    CScrollView::Dump(dc);
}

CPoemDoc* CHexView::GetDocument() const // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPoemDoc)));
    return (CPoemDoc*)m_pDocument;
}
#endif //_DEBUG


// CHexView message handlers
