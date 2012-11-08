// MainFrm.cpp : CMainFrame 类的实现
//

#include "StdAfx.h"
#include "ScrollWnd.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
    ON_WM_CREATE()
    ON_COMMAND(ID_VIEW_APPLE, &CMainFrame::OnViewApple)
END_MESSAGE_MAP()

static UINT indicators[] = {
    ID_SEPARATOR,           // 状态行指示器
    ID_INDICATOR_CAPS,
    ID_INDICATOR_NUM,
    ID_INDICATOR_SCRL,
};


// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
    // TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    //m_imglstIcon.Create(IDB_APPLE, 0, 0, RGB(192, 192, 192));

    CBitmap bm;
    //BITMAP bmp;
    //CImageList imgList;

    // 为 toolbar 加载 24bit 位图
    bm.LoadBitmap(IDB_APPLE);

    //bm2.LoadBitmap(IDB_APPLE_MASK);

    //bm.GetBitmap(&bmp);

    // ILC_MASK 指定是否使用掩码，掩码会在 CImageList 图和背景色混合时，滤掉特定的颜色
    // 有两种方式设置掩码: 使用一个单色位图，或者指定一个掩码颜色

    // Add() 的第一个参数是原图，第二个参数是掩码:

    // 使用掩码颜色时:
    //   没有 ILC_MASK 标志时，将 CImageList 图中为 掩码颜色 的像素颜色变为黑色。
    //   有 ILC_MASK 标志时，将 CImageList 图中为 掩码颜色 的像素颜色滤掉，显示背景色。
    // 试验后，发现对于 ILC_COLOR24 | ILC_MASK 起作用，而对于 8bit 图 ILC_COLOR8 | ILC_MASK 没有效果

    // 使用掩码位图时:
    //   (1) 使用 CImageList 图自己作为掩码，即 Add() 前后两个参数相同:
    //         没有 ILC_MASK 标志时，没有效果，只简单显示原 CImageList 图
    //         有 ILC_MASK 标志时，显示全黑图 (这和 CImageList 的实现有关，这里是 XP 下的效果，网上说在 Win7 下为简单显示原 CImageList 图)
    //   (2) Add() 前后两个参数 CBitmap 载入同一个位图，但却是两个 CBitmap 对象:
    //         无论有没有 ILC_MASK 标志，均没有效果，只简单显示原 CImageList 图。
    //   (3) 经过试验发现 CImageList 的掩码图，只使用二元混合方式(非 alpha 混合)，掩码图中只有两种颜色: 黑色, 白色，没有灰阶色
    //       如果掩码图使用的是彩图或灰阶图，所有非白色 (255,255,255) 的像素都认为是黑色，然后按下列方式混合:
    //         没有 ILC_MASK 标志时，没有效果，只简单显示原 CImageList 图
    //         有 ILC_MASK 标志时，掩码图中的黑色像素对应的原图像素保留下来，白色区域滤掉，显示背景色
    //       掩码图使用 4bit, 8bit, 24bit 位图都可以

    // 如果想使用 alpha 混合，可以直接使用 32bit 带 alpha 通道的 BMP 位图 或者 ICON 图标，然后使用 CImageList 的 ILC_COLOR32 标志创建。
    // 通过试验，XP 下 VC8 CImageList 可以在菜单项中成功显示 alpha 混合背景的 32bit 位图
    // 但是，如果使用 32bit BMP 位图 或 ICON 图标 存储小图像，文件大小较大，
    // 所以对于图像边缘可以截然区分颜色的位图，最好使用掩码颜色进行透明背景混合，通常使用的掩码颜色为 品红M (255,0,255)

    m_imglstIcon.Create(16, 16/*bmp.bmWidth*/, ILC_COLOR24 | ILC_MASK, 1/*bmp.bmWidth/bmp.bmHeight*/, 0);

    // CImageList 有一个背景色设置，用 GetBkColor()/SetBkColor 操作
    // 默认创建的 CImageList 使用背景色 CLR_NONE，意思为这样绘制 CImageList 原图：
    // (前景<---) CImageList 原图 | CImageList 掩码 | CImageList 背景色 | 窗口背景 (--->背景)
    // 上面 CImageList 背景色为透明，CImageList 原图做掩码滤色后直接画在窗口背景上。通常就使用这种绘制方法。

    TRACE("GetBkColor(): 0x%08X\n", m_imglstIcon.GetBkColor());
    TRACE("CLR_NONE: 0x%08X\n", CLR_NONE);
    COLORREF clr = ::GetSysColor(COLOR_BTNFACE);
    TRACE("GetSysColor(): 0x%08X R: %d, G: %d, B: %d\n", clr, GetRValue(clr), GetGValue(clr), GetBValue(clr));

    m_imglstIcon.Add(&bm, RGB(255, 0, 255)/*(CBitmap*)NULL*/);

    //HICON hIcon = g_TheApp.LoadIcon(IDI_APPLE);
    //m_imglstIcon.Add(hIcon);

    //imgList.Detach();
    bm.Detach();
    //bm2.Detach();

    const DWORD TOOLBAR_STYLE = WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC;
    if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, TOOLBAR_STYLE) || !m_wndToolBar.LoadToolBar(IDR_MAINFRAME)) {
        TRACE0("未能创建工具栏\n");
        return -1;      // 未能创建
    }

    if (!m_wndStatusBar.Create(this) || !m_wndStatusBar.SetIndicators(indicators, _countof(indicators))) {
        TRACE0("未能创建状态栏\n");
        return -1;      // 未能创建
    }

    // TODO: 如果不需要工具栏可停靠，则删除这三行
    m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
    EnableDocking(CBRS_ALIGN_ANY);
    DockControlBar(&m_wndToolBar);

    return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
    if( !CFrameWnd::PreCreateWindow(cs) )
        return FALSE;
    // TODO: 在此处通过修改
    //  CREATESTRUCT cs 来修改窗口类或样式

    return TRUE;
}


// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
    CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
    CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame 消息处理程序

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle , CWnd* pParentWnd , CCreateContext* pContext)
{
    if (!CFrameWnd::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
        return FALSE;
    return TRUE;
}

void CMainFrame::OnViewApple()
{
    MessageBox(_T("This is a test"), _T("Test"), MB_OK | MB_ICONINFORMATION);
}
