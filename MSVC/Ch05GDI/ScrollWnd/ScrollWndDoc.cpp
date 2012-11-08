// ScrollWndDoc.cpp : CScrollWndDoc 类的实现
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


// CScrollWndDoc 构造/析构

CScrollWndDoc::CScrollWndDoc()
{
    // TODO: 在此添加一次性构造代码

}

CScrollWndDoc::~CScrollWndDoc()
{
}

BOOL CScrollWndDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;

    // TODO: 在此添加重新初始化代码
    // (SDI 文档将重用该文档)

    return TRUE;
}




// CScrollWndDoc 序列化

void CScrollWndDoc::Serialize(CArchive& ar)
{
    if (ar.IsStoring()) {
        // TODO: 在此添加存储代码
    }
    else {
        // TODO: 在此添加加载代码
    }
}


// CScrollWndDoc 诊断

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


// CScrollWndDoc 命令
