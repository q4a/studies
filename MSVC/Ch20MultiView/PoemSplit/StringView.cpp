// StringView.cpp : implementation of the CStringView class
//

#include "StdAfx.h"
#include "PoemSplit.h"

#include "PoemDoc.h"
#include "StringView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStringView

IMPLEMENT_DYNCREATE(CStringView, CScrollView)

BEGIN_MESSAGE_MAP(CStringView, CScrollView)
    // Standard printing commands
    ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CStringView construction/destruction

CStringView::CStringView() : m_RectPrint(0, 0, 11520, -15120)
{
}

CStringView::~CStringView()
{
}

BOOL CStringView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs

    return CScrollView::PreCreateWindow(cs);
}

// CStringView drawing

void CStringView::OnDraw(CDC* pDC)
{
    int i, j, height;
    CString str;
    CFont font;
    TEXTMETRIC tm;

    CPoemDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    // draw a border
    pDC->Rectangle(m_RectPrint + CRect(0, 0, -20, 20));

    // draw horizontal and vertical rulers
    j = m_RectPrint.Width() / 1440;
    for (i = 0; i <= j; ++i) {
        str.Format(_T("%02d"), i);
        pDC->TextOut(i * 1440, 0, str);
    }
    j = -(m_RectPrint.Height() / 1440);
    for (i = 0; i <= j; ++i) {
        str.Format(_T("%02d"), i);
        pDC->TextOut(0, -i * 1440, str);
    }

    // print the poem 0.5 inch down and over, use 10-point roman font
    font.CreateFont(-200, 0, 0, 0, 400, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, _T("Times New Roman"));
    CFont* oldFont = (CFont*) pDC->SelectObject(&font);
    pDC->GetTextMetrics(&tm);
    height = tm.tmHeight + tm.tmExternalLeading;
    MYTRACE("font height = %d, internal leading = %d", height, tm.tmInternalLeading);
    j = (int) pDoc->m_StringArray.GetSize();
    for (i = 0; i < j; ++i)
        pDC->TextOut(720, -i * height - 720, pDoc->m_StringArray[i]);

    pDC->SelectObject(oldFont);
    MYTRACE("LOGPIXELSX = %d, LOGPIXELSY = %d", pDC->GetDeviceCaps(LOGPIXELSX), pDC->GetDeviceCaps(LOGPIXELSY));
    MYTRACE("HORZSIZE = %d, VERTSIZE = %d", pDC->GetDeviceCaps(HORZSIZE), pDC->GetDeviceCaps(VERTSIZE));
}

void CStringView::OnInitialUpdate()
{
    CScrollView::OnInitialUpdate();

    CSize sizeTotal(m_RectPrint.Width(), -m_RectPrint.Height());
    CSize sizePage(sizeTotal.cx / 2, sizeTotal.cy / 2);
    CSize sizeLine(sizeTotal.cx / 100, sizeTotal.cy / 100);
    SetScrollSizes(MM_TWIPS, sizeTotal, sizePage, sizeLine);
}


// CStringView printing

BOOL CStringView::OnPreparePrinting(CPrintInfo* pInfo)
{
    pInfo->SetMaxPage(1);
    return DoPreparePrinting(pInfo);
}

void CStringView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add extra initialization before printing
}

void CStringView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add cleanup after printing
}


// CStringView diagnostics

#ifdef _DEBUG
void CStringView::AssertValid() const
{
    CScrollView::AssertValid();
}

void CStringView::Dump(CDumpContext& dc) const
{
    CScrollView::Dump(dc);
}

CPoemDoc* CStringView::GetDocument() const // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPoemDoc)));
    return (CPoemDoc*)m_pDocument;
}
#endif //_DEBUG


// CStringView message handlers
