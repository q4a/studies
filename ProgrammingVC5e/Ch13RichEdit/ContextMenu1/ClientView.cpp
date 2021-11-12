// ClientView.cpp
//

#include "StdAfx.h"
#include "ContextMenu1.h"
#include "ClientView.h"

////////////////////////////////////////////////////////////////////////////////
// ����ܴ��ڿͻ����� CClientView
////////////////////////////////////////////////////////////////////////////////

// ��Ϣӳ��
BEGIN_MESSAGE_MAP(CClientView, CWnd)
    ON_WM_PAINT()
    ON_WM_LBUTTONDOWN()
    ON_WM_CONTEXTMENU()
    ON_COMMAND(ID_ITEM1, &CClientView::OnItem1)
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

void CClientView::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
    CMenu menu;
    menu.LoadMenu(IDR_MENU1);
    menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}

void CClientView::OnItem1()
{
    CString title;
    AfxGetMainWnd()->GetWindowText(title);
    this->MessageBox(_T("Push Item1!"), title, MB_OK | MB_ICONINFORMATION);
}
