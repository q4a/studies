// MainFrm.cpp : CMainFrame ���ʵ��
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
    ID_SEPARATOR,           // ״̬��ָʾ��
    ID_INDICATOR_CAPS,
    ID_INDICATOR_NUM,
    ID_INDICATOR_SCRL,
};


// CMainFrame ����/����

CMainFrame::CMainFrame()
{
    // TODO: �ڴ���ӳ�Ա��ʼ������
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

    // Ϊ toolbar ���� 24bit λͼ
    bm.LoadBitmap(IDB_APPLE);

    //bm2.LoadBitmap(IDB_APPLE_MASK);

    //bm.GetBitmap(&bmp);

    // ILC_MASK ָ���Ƿ�ʹ�����룬������� CImageList ͼ�ͱ���ɫ���ʱ���˵��ض�����ɫ
    // �����ַ�ʽ��������: ʹ��һ����ɫλͼ������ָ��һ��������ɫ

    // Add() �ĵ�һ��������ԭͼ���ڶ�������������:

    // ʹ��������ɫʱ:
    //   û�� ILC_MASK ��־ʱ���� CImageList ͼ��Ϊ ������ɫ ��������ɫ��Ϊ��ɫ��
    //   �� ILC_MASK ��־ʱ���� CImageList ͼ��Ϊ ������ɫ ��������ɫ�˵�����ʾ����ɫ��
    // ����󣬷��ֶ��� ILC_COLOR24 | ILC_MASK �����ã������� 8bit ͼ ILC_COLOR8 | ILC_MASK û��Ч��

    // ʹ������λͼʱ:
    //   (1) ʹ�� CImageList ͼ�Լ���Ϊ���룬�� Add() ǰ������������ͬ:
    //         û�� ILC_MASK ��־ʱ��û��Ч����ֻ����ʾԭ CImageList ͼ
    //         �� ILC_MASK ��־ʱ����ʾȫ��ͼ (��� CImageList ��ʵ���йأ������� XP �µ�Ч��������˵�� Win7 ��Ϊ����ʾԭ CImageList ͼ)
    //   (2) Add() ǰ���������� CBitmap ����ͬһ��λͼ����ȴ������ CBitmap ����:
    //         ������û�� ILC_MASK ��־����û��Ч����ֻ����ʾԭ CImageList ͼ��
    //   (3) �������鷢�� CImageList ������ͼ��ֻʹ�ö�Ԫ��Ϸ�ʽ(�� alpha ���)������ͼ��ֻ��������ɫ: ��ɫ, ��ɫ��û�лҽ�ɫ
    //       �������ͼʹ�õ��ǲ�ͼ��ҽ�ͼ�����зǰ�ɫ (255,255,255) �����ض���Ϊ�Ǻ�ɫ��Ȼ�����з�ʽ���:
    //         û�� ILC_MASK ��־ʱ��û��Ч����ֻ����ʾԭ CImageList ͼ
    //         �� ILC_MASK ��־ʱ������ͼ�еĺ�ɫ���ض�Ӧ��ԭͼ���ر�����������ɫ�����˵�����ʾ����ɫ
    //       ����ͼʹ�� 4bit, 8bit, 24bit λͼ������

    // �����ʹ�� alpha ��ϣ�����ֱ��ʹ�� 32bit �� alpha ͨ���� BMP λͼ ���� ICON ͼ�꣬Ȼ��ʹ�� CImageList �� ILC_COLOR32 ��־������
    // ͨ�����飬XP �� VC8 CImageList �����ڲ˵����гɹ���ʾ alpha ��ϱ����� 32bit λͼ
    // ���ǣ����ʹ�� 32bit BMP λͼ �� ICON ͼ�� �洢Сͼ���ļ���С�ϴ�
    // ���Զ���ͼ���Ե���Խ�Ȼ������ɫ��λͼ�����ʹ��������ɫ����͸��������ϣ�ͨ��ʹ�õ�������ɫΪ Ʒ��M (255,0,255)

    m_imglstIcon.Create(16, 16/*bmp.bmWidth*/, ILC_COLOR24 | ILC_MASK, 1/*bmp.bmWidth/bmp.bmHeight*/, 0);

    // CImageList ��һ������ɫ���ã��� GetBkColor()/SetBkColor ����
    // Ĭ�ϴ����� CImageList ʹ�ñ���ɫ CLR_NONE����˼Ϊ�������� CImageList ԭͼ��
    // (ǰ��<---) CImageList ԭͼ | CImageList ���� | CImageList ����ɫ | ���ڱ��� (--->����)
    // ���� CImageList ����ɫΪ͸����CImageList ԭͼ��������ɫ��ֱ�ӻ��ڴ��ڱ����ϡ�ͨ����ʹ�����ֻ��Ʒ�����

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
        TRACE0("δ�ܴ���������\n");
        return -1;      // δ�ܴ���
    }

    if (!m_wndStatusBar.Create(this) || !m_wndStatusBar.SetIndicators(indicators, _countof(indicators))) {
        TRACE0("δ�ܴ���״̬��\n");
        return -1;      // δ�ܴ���
    }

    // TODO: �������Ҫ��������ͣ������ɾ��������
    m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
    EnableDocking(CBRS_ALIGN_ANY);
    DockControlBar(&m_wndToolBar);

    return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
    if( !CFrameWnd::PreCreateWindow(cs) )
        return FALSE;
    // TODO: �ڴ˴�ͨ���޸�
    //  CREATESTRUCT cs ���޸Ĵ��������ʽ

    return TRUE;
}


// CMainFrame ���

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


// CMainFrame ��Ϣ�������

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
