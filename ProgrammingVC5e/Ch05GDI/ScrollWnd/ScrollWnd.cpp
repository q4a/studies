// ScrollWnd.cpp : ����Ӧ�ó��������Ϊ��
//

#include "StdAfx.h"
#include "ScrollWnd.h"
#include "MainFrm.h"

#include "ScrollWndDoc.h"
#include "ScrollWndView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CScrollWndApp

BEGIN_MESSAGE_MAP(CScrollWndApp, CWinApp)
    ON_COMMAND(ID_APP_ABOUT, &CScrollWndApp::OnAppAbout)
    // �����ļ��ı�׼�ĵ�����
    ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
    ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()

// CScrollWndApp ����

CScrollWndApp::CScrollWndApp()
{
    // TODO: �ڴ˴���ӹ�����룬
    // ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CScrollWndApp ����

CScrollWndApp g_TheApp;


// CScrollWndApp ��ʼ��

BOOL CScrollWndApp::InitInstance()
{
    // ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
    // ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
    //����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
    INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwSize = sizeof(InitCtrls);
    // ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
    // �����ؼ��ࡣ
    InitCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&InitCtrls);

    CWinApp::InitInstance();

    // ��ʼ�� OLE ��
    if (!AfxOleInit()) {
        AfxMessageBox(IDP_OLE_INIT_FAILED);
        return FALSE;
    }
    AfxEnableControlContainer();

    // ��׼��ʼ��
    // ���δʹ����Щ���ܲ�ϣ����С
    // ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
    // ����Ҫ���ض���ʼ������

    // �������ڴ洢���õ�ע�����
    // TODO: Ӧ�ʵ��޸ĸ��ַ�����
    // �����޸�Ϊ��˾����֯��
    SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
    LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)
    // ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
    // �������ĵ�����ܴ��ں���ͼ֮�������
    CSingleDocTemplate* pDocTemplate;
    pDocTemplate = new CSingleDocTemplate(
        IDR_MAINFRAME,
        RUNTIME_CLASS(CScrollWndDoc),
        RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
        RUNTIME_CLASS(CScrollWndView));
    if (!pDocTemplate)
        return FALSE;
    AddDocTemplate(pDocTemplate);

    // ������׼������DDE�����ļ�������������
    CCommandLineInfo cmdInfo;
    ParseCommandLine(cmdInfo);

    // ��������������ָ����������
    // �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
    if (!ProcessShellCommand(cmdInfo))
        return FALSE;

    // Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
    m_pMainWnd->ShowWindow(SW_SHOW);
    m_pMainWnd->UpdateWindow();
    // �������к�׺ʱ�ŵ��� DragAcceptFiles
    // �� SDI Ӧ�ó����У���Ӧ�� ProcessShellCommand  ֮����
    return TRUE;
}

int CScrollWndApp::ExitInstance()
{
    return CWinApp::ExitInstance();
}

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog {
public:
    CAboutDlg();

// �Ի�������
    enum { IDD = IDD_ABOUTBOX };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
    DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}

// �������жԻ����Ӧ�ó�������
void CScrollWndApp::OnAppAbout()
{
    CAboutDlg aboutDlg;
    aboutDlg.DoModal();
}
