// MyRebarView.cpp : implementation of the CMyRebarView class
//

#include "StdAfx.h"
#include "MyRebar.h"

#include "MyRebarDoc.h"
#include "MyRebarView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyRebarView

IMPLEMENT_DYNCREATE(CMyRebarView, CView)

BEGIN_MESSAGE_MAP(CMyRebarView, CView)
END_MESSAGE_MAP()

// CMyRebarView construction/destruction

CMyRebarView::CMyRebarView()
{
	// TODO: add construction code here

}

CMyRebarView::~CMyRebarView()
{
}

BOOL CMyRebarView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMyRebarView drawing

void CMyRebarView::OnDraw(CDC* /*pDC*/)
{
	CMyRebarDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMyRebarView diagnostics

#ifdef _DEBUG
void CMyRebarView::AssertValid() const
{
	CView::AssertValid();
}

void CMyRebarView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyRebarDoc* CMyRebarView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyRebarDoc)));
	return (CMyRebarDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyRebarView message handlers
