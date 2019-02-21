// RichEdit1View.cpp : implementation of the CRichEdit1View class
//

#include "StdAfx.h"
#include "RichEdit1.h"

#include "RichEdit1Doc.h"
#include "FontPage.h"
#include "EffectPage.h"
#include "ColorPage.h"
#include "FontSizePage.h"
#include "FontSheet.h"
#include "RichEdit1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRichEdit1View

IMPLEMENT_DYNCREATE(CRichEdit1View, CView)

BEGIN_MESSAGE_MAP(CRichEdit1View, CView)
    ON_COMMAND(ID_GET_SELFMT, &CRichEdit1View::OnGetSelFormat)
    ON_COMMAND(ID_SET_SELFMT, &CRichEdit1View::OnSetSelFormat)
    ON_COMMAND(ID_TRANSFER_GETDATA, &CRichEdit1View::OnTransferGetdata)
    ON_COMMAND(ID_TRANSFER_STOREDATA, &CRichEdit1View::OnTransferStoredata)
    ON_UPDATE_COMMAND_UI(ID_TRANSFER_STOREDATA, &CRichEdit1View::OnUpdateTransferStoredata)
    ON_COMMAND(ID_EDIT_CLEAR_ALL, &CRichEdit1View::OnEditClearAll)
    ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR_ALL, &CRichEdit1View::OnUpdateEditClearAll)
    ON_WM_CREATE()
    ON_WM_SIZE()
    ON_COMMAND(ID_FORMAT_DEFAULT, &CRichEdit1View::OnFormatDefault)
    ON_COMMAND(ID_FORMAT_SELECTION, &CRichEdit1View::OnFormatSelection)
    ON_UPDATE_COMMAND_UI(ID_FORMAT_SELECTION, &CRichEdit1View::OnUpdateFormatSelection)
    ON_MESSAGE(CFontPage::WM_USERAPPLY, OnUserApply)
END_MESSAGE_MAP()

// CRichEdit1View construction/destruction

CRichEdit1View::CRichEdit1View() :
    m_FormatType(FORMAT_DEFAULT), m_FontSheet(_T(""))
{
}

CRichEdit1View::~CRichEdit1View()
{
}

BOOL CRichEdit1View::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs

    return CView::PreCreateWindow(cs);
}

// CRichEdit1View drawing

void CRichEdit1View::OnDraw(CDC* /*pDC*/)
{
    CRichEdit1Doc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    // TODO: add draw code for native data here
}


// CRichEdit1View diagnostics

#ifdef _DEBUG
void CRichEdit1View::AssertValid() const
{
    CView::AssertValid();
}

void CRichEdit1View::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CRichEdit1Doc* CRichEdit1View::GetDocument() const // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRichEdit1Doc)));
    return (CRichEdit1Doc*) m_pDocument;
}
#endif //_DEBUG

// 得到选择文本的字体
void CRichEdit1View::OnGetSelFormat()
{
    CHARFORMAT2 cf;
    ZeroMemory(&cf, sizeof(cf));
    cf.cbSize = sizeof(cf);
    cf.dwMask = CFM_FACE;
    DWORD mask = m_RichEdit.GetSelectionCharFormat(cf);
    MYTRACE("Font in selection is: %s", cf.szFaceName);
}

// 设置选择文本的字体
void CRichEdit1View::OnSetSelFormat()
{
    CHARFORMAT2 cf;
    ZeroMemory(&cf, sizeof(cf));
    cf.cbSize = sizeof(cf);
    cf.dwMask = CFM_FACE;

    _tcscpy_s(cf.szFaceName, _countof(cf.szFaceName), _T("Microsoft YaHei"));
    BOOL ret = m_RichEdit.SetSelectionCharFormat(cf);
    ret = m_RichEdit.SetDefaultCharFormat(cf);
}

void CRichEdit1View::OnTransferGetdata()
{
    m_RichEdit.SetWindowText(GetDocument()->m_Text);
    m_RichEdit.SetModify(TRUE);
}

void CRichEdit1View::OnTransferStoredata()
{
    m_RichEdit.GetWindowText(GetDocument()->m_Text);
    m_RichEdit.SetModify(FALSE);
}

void CRichEdit1View::OnUpdateTransferStoredata(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(m_RichEdit.GetModify());
}

void CRichEdit1View::OnEditClearAll()
{
    m_RichEdit.SetWindowText(_T(""));
}

void CRichEdit1View::OnUpdateEditClearAll(CCmdUI *pCmdUI)
{
    CString text;
    m_RichEdit.GetWindowText(text);
    pCmdUI->Enable(!text.IsEmpty());
}

int CRichEdit1View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;

    CRect rect(0, 0, 0, 0);
    const DWORD RICH_STYLE = ES_AUTOVSCROLL | ES_MULTILINE | ES_WANTRETURN | WS_CHILD | WS_VISIBLE | WS_VSCROLL;
    m_RichEdit.Create(RICH_STYLE, rect, this, ID_RICHEDIT);
    return 0;
}

void CRichEdit1View::OnSize(UINT nType, int cx, int cy)
{
    CView::OnSize(nType, cx, cy);
    CRect rect;
    GetClientRect(&rect);
    m_RichEdit.SetWindowPos(&wndTop, 0, 0, rect.Width(), rect.Height(), SWP_SHOWWINDOW);
}

void CRichEdit1View::OnInitialUpdate()
{
    CView::OnInitialUpdate();

    // 因为键盘输入的字体和从 OnTransferGetdata 输入到 RichEdit 的字体不同, 所以禁用自定义字体 (RichEdit 退化成 Edit 控件)
    // m_RichEdit.SetTextMode(TM_PLAINTEXT);

#if 1
    // 设定字体, 但测试发现不起作用. 初步判断是字体设置信息不足, 因为可以设定字体粗细
    CHARFORMAT2 cf;
    ZeroMemory(&cf, sizeof(cf));
    cf.cbSize = sizeof(cf);
    cf.dwMask = CFM_FACE | CFM_BOLD;
    _tcscpy_s(cf.szFaceName, _countof(cf.szFaceName), _T("System"));
    BOOL ret = m_RichEdit.SetDefaultCharFormat(cf);
#endif
}

void CRichEdit1View::OnFormatDefault()
{
    m_FontSheet.SetTitle(_T("Default Format"));
    m_FormatType = FORMAT_DEFAULT;
    m_FontSheet.DoModal();
}

void CRichEdit1View::OnFormatSelection()
{
    m_FontSheet.SetTitle(_T("Selection Format"));
    m_FormatType = FORMAT_SELECT;
    m_FontSheet.DoModal();
}

void CRichEdit1View::OnUpdateFormatSelection(CCmdUI *pCmdUI)
{
    long start, end;
    m_RichEdit.GetSel(start, end);
    pCmdUI->Enable(start != end);   // 当选择不为空时, 才激活菜单项
}

LRESULT CRichEdit1View::OnUserApply(WPARAM wparam, LPARAM lparam)
{
    MYTRACE("enter");
    CHARFORMAT2 cf;
    GetFormat(cf);

    if (m_FormatType == FORMAT_DEFAULT)
        m_RichEdit.SetDefaultCharFormat(cf);
    else if (m_FormatType == FORMAT_SELECT)
        m_RichEdit.SetSelectionCharFormat(cf);

    return 0;
}

void CRichEdit1View::GetFormat(CHARFORMAT2& cf)
{
    ZeroMemory(&cf, sizeof(cf));
    cf.cbSize = sizeof(cf);
    cf.dwMask = CFM_BOLD | CFM_COLOR | CFM_FACE | CFM_ITALIC | CFM_SIZE | CFM_UNDERLINE;

    // 字体效果
    cf.dwEffects = (m_FontSheet.m_EffectPage.m_Bold ? CFE_BOLD : 0) |
                   (m_FontSheet.m_EffectPage.m_Italic ? CFE_ITALIC : 0) |
                   (m_FontSheet.m_EffectPage.m_Underline ? CFE_UNDERLINE : 0);

    // 字体大小
    cf.yHeight = m_FontSheet.m_FontSizePage.m_FontSize * 20;

    // 字体颜色
    cf.crTextColor = m_FontSheet.m_ColorPage.GetColor();

    // 字体名称
    _tcscpy_s(cf.szFaceName, _countof(cf.szFaceName), m_FontSheet.m_FontPage.GetFont());
}
