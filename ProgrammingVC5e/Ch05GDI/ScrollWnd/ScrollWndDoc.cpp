// ScrollWndDoc.cpp : CScrollWndDoc ���ʵ��
//

#include "StdAfx.h"
#include "ScrollWnd.h"

#include "ScrollWndDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CScrollWndDoc

IMPLEMENT_DYNCREATE(CScrollWndDoc, CDocument)

BEGIN_MESSAGE_MAP(CScrollWndDoc, CDocument)
END_MESSAGE_MAP()


// CScrollWndDoc ����/����

CScrollWndDoc::CScrollWndDoc()
{
    // TODO: �ڴ����һ���Թ������

}

CScrollWndDoc::~CScrollWndDoc()
{
}

BOOL CScrollWndDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;

    // TODO: �ڴ�������³�ʼ������
    // (SDI �ĵ������ø��ĵ�)

    return TRUE;
}




// CScrollWndDoc ���л�

void CScrollWndDoc::Serialize(CArchive& ar)
{
    if (ar.IsStoring()) {
        // TODO: �ڴ���Ӵ洢����
    }
    else {
        // TODO: �ڴ���Ӽ��ش���
    }
}


// CScrollWndDoc ���

#ifdef _DEBUG
void CScrollWndDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CScrollWndDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG


// CScrollWndDoc ����
