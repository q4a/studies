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
#include "ProgBarEvent.h"
#include "ClientView.h"

////////////////////////////////////////////////////////////////////////////////
// ����ܴ��ڿͻ����� CClientView
////////////////////////////////////////////////////////////////////////////////

// ��Ϣӳ��
BEGIN_MESSAGE_MAP(CClientView, CWnd)
    ON_WM_PAINT()
    ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

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

void CClientView::OnDraw(CDC* pDC)
{
    ASSERT_VALID(pDC);
    pDC->SelectStockObject(m_Color);
    pDC->Ellipse(&m_Ellipse);
}

void CClientView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo/* = 0*/)
{
    // NOTE: �� OnPrepareDC ���趨ӳ�䷽ʽ������ԭ��
    pDC->SetMapMode(MM_TEXT);
}

void CClientView::OnLButtonDown(UINT nFlags, CPoint point)
{
    CClientDC dc(this);
    OnPrepareDC(&dc);
    CRect rect(m_Ellipse);
    // ת�����豸��������жϵ��λ��, ��Ϊ point ���豸����
    dc.LPtoDP(&rect);

    CRgn rgn;
    rgn.CreateEllipticRgnIndirect(&rect);
    // ��������λ������Բ�ڲ�, ��任��ɫ
    if (rgn.PtInRegion(point))
        m_Color = (m_Color == GRAY_BRUSH ? WHITE_BRUSH : GRAY_BRUSH);
    // ʹ��Բ��Ӿ�����Ч, ֻ�ػ��ⲿ������
    InvalidateRect(rect);
}
