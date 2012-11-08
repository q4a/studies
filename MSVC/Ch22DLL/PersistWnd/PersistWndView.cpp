// PersistWndView.cpp : implementation of the CPersistWndView class
//

#include "StdAfx.h"
#include "PersistWnd.h"

#include "PersistWndDoc.h"
#include "PersistWndView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPersistWndView

IMPLEMENT_DYNCREATE(CPersistWndView, CView)

BEGIN_MESSAGE_MAP(CPersistWndView, CView)
END_MESSAGE_MAP()

// CPersistWndView construction/destruction

CPersistWndView::CPersistWndView()
{
	// TODO: add construction code here

}

CPersistWndView::~CPersistWndView()
{
}

BOOL CPersistWndView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPersistWndView drawing

void CPersistWndView::OnDraw(CDC* /*pDC*/)
{
	CPersistWndDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CPersistWndView diagnostics

#ifdef _DEBUG
void CPersistWndView::AssertValid() const
{
	CView::AssertValid();
}

void CPersistWndView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPersistWndDoc* CPersistWndView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPersistWndDoc)));
	return (CPersistWndDoc*)m_pDocument;
}
#endif //_DEBUG


// CPersistWndView message handlers
