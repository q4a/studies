////////////////////////////////////////////////////////////////////////////////
// ��    �� : ClientView.cpp
// ����˵�� :
//   ����ܴ��ڿͻ���
//
// ��    �� : 1.0
// ��    �� : Breaker Zhao <breaker.zy_AT_gmail>
// ��    �� : 2010-10
////////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "ShowBmp.h"
#include "ClientView.h"
#include "dib.h"

////////////////////////////////////////////////////////////////////////////////
// ����ܴ��ڿͻ����� CClientView
////////////////////////////////////////////////////////////////////////////////

// ��Ϣӳ��
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

    cs.dwExStyle |= WS_EX_CLIENTEDGE;   // �����³��߿���ʽ (sunken edge)
    cs.style &= ~WS_BORDER;             // ȥ���߿�
    cs.lpszClass = AfxRegisterWndClass(0, LoadCursor(0, IDC_ARROW), (HBRUSH) (COLOR_WINDOW + 1), 0);
    return TRUE;
}

void CClientView::OnPaint()
{
    // NOTE: ��Ҫ���ø��� CWnd::OnPaint ��ͼ
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
    // NOTE: �� OnPrepareDC ���趨ӳ�䷽ʽ������ԭ��
    pDC->SetMapMode(MM_TEXT);
}
