// MouseStatusView.cpp : implementation of the CMouseStatusView class
//

#include "StdAfx.h"
#include "MouseStatus.h"

#include "MouseStatusDoc.h"
#include "MouseStatusView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMouseStatusView

IMPLEMENT_DYNCREATE(CMouseStatusView, CView)

BEGIN_MESSAGE_MAP(CMouseStatusView, CView)
    ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CMouseStatusView construction/destruction

CMouseStatusView::CMouseStatusView()
{
    // TODO: add construction code here

}

CMouseStatusView::~CMouseStatusView()
{
}

BOOL CMouseStatusView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs

    return CView::PreCreateWindow(cs);
}

// CMouseStatusView drawing

void CMouseStatusView::OnDraw(CDC* pDC)
{
    CMouseStatusDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    pDC->TextOut(0, 0, _T("Watch the status bar while you move and click the mouse."));
}


// CMouseStatusView diagnostics

#ifdef _DEBUG
void CMouseStatusView::AssertValid() const
{
    CView::AssertValid();
}

void CMouseStatusView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CMouseStatusDoc* CMouseStatusView::GetDocument() const // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMouseStatusDoc)));
    return (CMouseStatusDoc*)m_pDocument;
}
#endif //_DEBUG


// CMouseStatusView message handlers

void CMouseStatusView::OnMouseMove(UINT nFlags, CPoint point)
{
    CString str;
    CMainFrame* frame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
    CStatusBar* status = &(frame->m_wndStatusBar);
    if (status != NULL) {
        str.Format(_T("x = %d"), point.x);
        status->SetPaneText(0, str);
        str.Format(_T("y = %d"), point.y);
        status->SetPaneText(1, str);
    }
}
