// IEBrowserView.cpp : implementation of the CIEBrowserView class
//

#include "StdAfx.h"
#include "IEBrowser.h"

#include "IEBrowserDoc.h"
#include "WebBrowser.h"
#include "IEBrowserView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIEBrowserView

IMPLEMENT_DYNCREATE(CIEBrowserView, CView)

BEGIN_MESSAGE_MAP(CIEBrowserView, CView)
    ON_WM_CREATE()
    ON_WM_SIZE()
END_MESSAGE_MAP()

// ActiveX 控件的消息映射
BEGIN_EVENTSINK_MAP(CIEBrowserView, CView)
// ON_EVENT() 的最后参数 VTS_* 都是在 afxdisp.h 中定义的字符串常量，靠空字符拼接，用来描述事件处理函数的参数类型列表
ON_EVENT(CIEBrowserView, ID_BROWSER_SEARCH, 100, CIEBrowserView::OnBeforeNavigateExplore1, VTS_BSTR VTS_I4 VTS_BSTR VTS_PVARIANT VTS_BSTR VTS_PBOOL)
ON_EVENT(CIEBrowserView, ID_BROWSER_TARGET, 113, CIEBrowserView::OnTitleChangeExplorer2, VTS_BSTR)
END_EVENTSINK_MAP()

LPCTSTR CIEBrowserView::SearchURL = _T(DEFAULT_URL);

// CIEBrowserView construction/destruction

CIEBrowserView::CIEBrowserView()
{
    // TODO: add construction code here

}

CIEBrowserView::~CIEBrowserView()
{
}

BOOL CIEBrowserView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs

    return CView::PreCreateWindow(cs);
}

// CIEBrowserView drawing

void CIEBrowserView::OnDraw(CDC* /*pDC*/)
{
    CIEBrowserDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    // TODO: add draw code for native data here
}


// CIEBrowserView diagnostics

#ifdef _DEBUG
void CIEBrowserView::AssertValid() const
{
    CView::AssertValid();
}

void CIEBrowserView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CIEBrowserDoc* CIEBrowserView::GetDocument() const // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIEBrowserDoc)));
    return (CIEBrowserDoc*)m_pDocument;
}
#endif //_DEBUG


// CIEBrowserView message handlers

int CIEBrowserView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;

    // 创建两个 IE 浏览器 ActiveX 控件窗口 (CWebBrowser)

    DWORD style = WS_VISIBLE | WS_CHILD;
    if (!m_SearchBrowser.Create(NULL, style, CRect(0, 0, 100, 100), this, ID_BROWSER_SEARCH)) {
        AfxMessageBox(_T("Unable to create search browser (ActiveX Control)"));
        return -1;
    }

    m_SearchBrowser.Navigate(SearchURL, NULL, NULL, NULL, NULL);

    if (!m_TargetBrowser.Create(NULL, style, CRect(0, 0, 100, 100), this, ID_BROWSER_TARGET)) {
        AfxMessageBox(_T("Unable to create target browser (ActiveX Control)"));
        return -1;
    }

    m_TargetBrowser.GoHome();

    return 0;
}

void CIEBrowserView::OnSize(UINT nType, int cx, int cy)
{
    CView::OnSize(nType, cx, cy);

    // 让两个 ActiveX 浏览器子窗口 随父窗口大小变化，对分父窗口大小

    CRect rectClient;
    GetClientRect(&rectClient);

    CRect rectTarget(rectClient);
    rectTarget.right = rectClient.right / 2;

    CRect rectSearch(rectClient);
    rectSearch.left = rectClient.right / 2;

    //m_TargetBrowser.SetWindowPos(&CWnd::wndTop, rectTarget.left, rectTarget.top, rectTarget.right, rectTarget.bottom, SWP_SHOWWINDOW);
    m_TargetBrowser.put_Width(rectTarget.Width());
    m_TargetBrowser.put_Height(rectTarget.Height());
    m_TargetBrowser.UpdateWindow();

    //m_SearchBrowser.SetWindowPos(&CWnd::wndTop, rectSearch.left, rectSearch.top, rectSearch.right, rectSearch.bottom, SWP_SHOWWINDOW);
    m_SearchBrowser.put_Left(rectSearch.left);
    m_SearchBrowser.put_Width(rectSearch.Width());
    m_SearchBrowser.put_Height(rectSearch.Height());
    m_SearchBrowser.UpdateWindow();
}

// BUG: 这个事件 (100) 在 IE7 + VS2005 中没有触发，估计是事件 ID 不对
void CIEBrowserView::OnBeforeNavigateExplore1(
    LPCTSTR URL, long Flags, LPCTSTR TargetFrameName,
    VARIANT* PostData, LPCTSTR Headers, BOOL* Cancel
)
{
    TRACE(_T("*** OnBeforeNavigateExplore1(): URL=%s\n"), URL);

    if (_tcsncmp(URL, SearchURL, _tcslen(SearchURL)) == 0)
        return;

    m_TargetBrowser.Navigate(URL, NULL, NULL, PostData, NULL);
    *Cancel = TRUE;
}

void CIEBrowserView::OnTitleChangeExplorer2(LPCTSTR Text)
{
    // CAUTION:
    // 有种情况使得窗口未准备好前，就触发事件进入该处理函数，所以先要判断窗口的
    // 有效性，然后在窗口上操作
    CWnd* wnd = AfxGetApp()->m_pMainWnd;
    if (wnd != NULL) {
        // 设定标题
        if (::IsWindow(wnd->m_hWnd))
            wnd->SetWindowText(Text);
    }
}