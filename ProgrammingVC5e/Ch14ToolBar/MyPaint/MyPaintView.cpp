// MyPaintView.cpp : implementation of the CMyPaintView class
//

#include "StdAfx.h"
#include "MyPaint.h"

#include "MyPaintDoc.h"
#include "MyPaintView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyPaintView

IMPLEMENT_DYNCREATE(CMyPaintView, CView)

BEGIN_MESSAGE_MAP(CMyPaintView, CView)
    ON_COMMAND(ID_DRAW_CIRCLE, &CMyPaintView::OnDrawCircle)
    ON_UPDATE_COMMAND_UI(ID_DRAW_CIRCLE, &CMyPaintView::OnUpdateDrawCircle)
    ON_COMMAND(ID_DRAW_PATTERN, &CMyPaintView::OnDrawPattern)
    ON_UPDATE_COMMAND_UI(ID_DRAW_PATTERN, &CMyPaintView::OnUpdateDrawPattern)
    ON_COMMAND(ID_DRAW_SQUARE, &CMyPaintView::OnDrawSquare)
    ON_UPDATE_COMMAND_UI(ID_DRAW_SQUARE, &CMyPaintView::OnUpdateDrawSquare)
END_MESSAGE_MAP()

// CMyPaintView construction/destruction

CMyPaintView::CMyPaintView() :
    m_Rect(0, 0, 100, 100), m_Circle(TRUE), m_Pattern(FALSE)
{
}

CMyPaintView::~CMyPaintView()
{
}

BOOL CMyPaintView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs

    return CView::PreCreateWindow(cs);
}

// CMyPaintView drawing

void CMyPaintView::OnDraw(CDC* pDC)
{
    CMyPaintDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    CBrush brush(HS_BDIAGONAL, 0);  // diagonal pattern
    if (m_Pattern)
        pDC->SelectObject(&brush);
    else
        pDC->SelectStockObject(WHITE_BRUSH);

    if (m_Circle)
        pDC->Ellipse(m_Rect);
    else
        pDC->Rectangle(m_Rect);

    pDC->SelectStockObject(WHITE_BRUSH);    // deselect brush
}


// CMyPaintView diagnostics

#ifdef _DEBUG
void CMyPaintView::AssertValid() const
{
    CView::AssertValid();
}

void CMyPaintView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CMyPaintDoc* CMyPaintView::GetDocument() const // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyPaintDoc)));
    return (CMyPaintDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyPaintView message handlers

void CMyPaintView::OnDrawCircle()
{
    m_Circle = TRUE;
    m_Rect += CPoint(25, 25);
    InvalidateRect(m_Rect);
}

void CMyPaintView::OnUpdateDrawCircle(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(!m_Circle);
}

void CMyPaintView::OnDrawPattern()
{
    m_Pattern ^= 1;
}

void CMyPaintView::OnUpdateDrawPattern(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck(m_Pattern);
}

void CMyPaintView::OnDrawSquare()
{
    m_Circle = FALSE;
    m_Rect += CPoint(25, 25);
    InvalidateRect(m_Rect);
}

void CMyPaintView::OnUpdateDrawSquare(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(m_Circle);
}
