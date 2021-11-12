// BmpResView.cpp : implementation of the CBmpResView class
//

#include "StdAfx.h"
#include "BmpRes.h"

#include "BmpResDoc.h"
#include "BmpResView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CBmpResView

IMPLEMENT_DYNCREATE(CBmpResView, CView)

BEGIN_MESSAGE_MAP(CBmpResView, CView)
END_MESSAGE_MAP()

// CBmpResView construction/destruction

CBmpResView::CBmpResView()
{
}

CBmpResView::~CBmpResView()
{
}

BOOL CBmpResView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs
    return CView::PreCreateWindow(cs);
}

// CBmpResView drawing

void CBmpResView::OnDraw(CDC* pDC)
{
    CBmpResDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    // NOTE:
    // ���ͷ� GDI ������Դǰ, Ҫ��֤û�б�ѡ�� DC, ���� DC ��ѡ���� GDI ����, CDC ��������ʱ�����ѡ������
    // �� GDI �� (CGdiObject, CBitmap, CBrush...) �� DeleteObject() �����ͷ� GDI ��Դ, GDI ���������, Ҳ���ͷ� GDI ����
    // ���� CBitmap bmp; CDC dcMem; �Ķ���˳�����Ҫ: ���� bmp, ���� dcMem, ������֤������ dcMem (�� DC ѡ�� GDI λͼ), ������ bmp (ɾ�� GDI λͼ)
    CBitmap bmp;    // 1
    CDC dcMem;      // 2
    bmp.LoadBitmap(IDB_BMP01);
    dcMem.CreateCompatibleDC(pDC);
    dcMem.SelectObject(&bmp);
    pDC->BitBlt(50, 50, 256, 512, &dcMem, 0, 0, SRCCOPY);
}

// CBmpResView diagnostics
#ifdef _DEBUG
void CBmpResView::AssertValid() const
{
    CView::AssertValid();
}

void CBmpResView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CBmpResDoc* CBmpResView::GetDocument() const // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBmpResDoc)));
    return (CBmpResDoc*) m_pDocument;
}
#endif //_DEBUG
