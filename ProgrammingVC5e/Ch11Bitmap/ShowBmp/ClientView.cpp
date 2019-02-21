////////////////////////////////////////////////////////////////////////////////
// 文    件 : ClientView.cpp
// 功能说明 :
//   主框架窗口客户区
//
// 版    本 : 1.0
// 作    者 : Breaker Zhao <breaker.zy_AT_gmail>
// 日    期 : 2010-10
////////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "ShowBmp.h"
#include "ClientView.h"
#include "dib.h"

////////////////////////////////////////////////////////////////////////////////
// 主框架窗口客户区类 CClientView
////////////////////////////////////////////////////////////////////////////////

// 消息映射
BEGIN_MESSAGE_MAP(CClientView, CWnd)
    ON_WM_PAINT()
END_MESSAGE_MAP()

CClientView::CClientView() : m_Dib(new CDib)
{
}

CClientView::~CClientView()
{
    delete m_Dib;
}

BOOL CClientView::PreCreateWindow(CREATESTRUCT& cs)
{
    if (!CWnd::PreCreateWindow(cs))
        return FALSE;

    cs.dwExStyle |= WS_EX_CLIENTEDGE;   // 增加下沉边框样式 (sunken edge)
    cs.style &= ~WS_BORDER;             // 去掉边框
    cs.lpszClass = AfxRegisterWndClass(0, LoadCursor(0, IDC_ARROW), (HBRUSH) (COLOR_WINDOW + 1), 0);
    return TRUE;
}

void CClientView::OnPaint()
{
    // NOTE: 不要调用父类 CWnd::OnPaint 绘图
    CPaintDC dc(this);
    OnPrepareDC(&dc);
    OnDraw(&dc);
}

BOOL CClientView::LoadBmp(const TCHAR* path)
{
#define _USE_MAPPING_FILE

    ASSERT(m_Dib != 0);
#ifdef _USE_MAPPING_FILE
    if (!m_Dib->AttachMapFile(path, TRUE))
        return FALSE;
#else
    CFile file;
    file.Open(path, CFile::modeRead);
    if (!m_Dib->Read(&file))
        return FALSE;
#endif  // _USE_MAPPING_FILE

    Invalidate();
    CClientDC dc(this);
    m_Dib->SetSystemPalette(&dc);
    return TRUE;
}

void CClientView::OnDraw(CDC* pDC)
{
    ASSERT_VALID(pDC);

    static BOOL first = TRUE;
    if (first) {
        SHOWBMP_TRACE("bpp=%d", pDC->GetDeviceCaps(BITSPIXEL));
        first = FALSE;
    }

    ASSERT(m_Dib != 0);
    BeginWaitCursor();
    m_Dib->UsePalette(pDC);
    m_Dib->Draw(pDC, CPoint(10, 10), m_Dib->GetDimensions());
    EndWaitCursor();
}

void CClientView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo/* = 0*/)
{
    // NOTE: 在 OnPrepareDC 中设定映射方式和坐标原点
    pDC->SetMapMode(MM_TEXT);
}
