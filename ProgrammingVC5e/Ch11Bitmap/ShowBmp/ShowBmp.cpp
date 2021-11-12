////////////////////////////////////////////////////////////////////////////////
// ��    �� : ShowBmp.cpp
// ����˵�� :
//   �������ںͳ�ʼ��
//   ShowBmp �� MFC �����ڳ��򹤳�ģ��, �� Doc/View ģ��
//
// ��    �� : 1.0
// ��    �� : Breaker Zhao <breaker.zy_AT_gmail>
// ��    �� : 2010-10
////////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "ShowBmp.h"
#include "ClientView.h"
#include "MainFrame.h"

////////////////////////////////////////////////////////////////////////////////
// ȫ����
////////////////////////////////////////////////////////////////////////////////

// Ӧ�ó���ʵ��
CShowBmpApp g_ShowBmpApp;

////////////////////////////////////////////////////////////////////////////////
// Ӧ�ó����� CShowBmpApp
////////////////////////////////////////////////////////////////////////////////

BOOL CShowBmpApp::InitInstance()
{
    CWinApp::InitInstance();

    // ���װ���ļ� (manifest) ��ָ��ʹ�� Windows ͨ�ÿؼ� ComCtl32.dll 6.0+ �汾, ���� Windows XP ����Ҫ���� InitCommonControlsEx(), ���򴰿ڴ�����ʧ��
    // ���ó������ܹ�ʹ�õ�ͨ�ÿؼ���, ICC_WIN95_CLASSES ��ʾ���� Win95 ͨ�ÿؼ�
    INITCOMMONCONTROLSEX initCtrls;
    initCtrls.dwSize = sizeof(initCtrls);
    initCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&initCtrls);

    // ������ģ��ȫ·��, ���ù���Ŀ¼
    InitModulePath(MAX_PATH);
    InitWorkDir(GetModuleDir());

    // ���� CRT locale, VC 2005 �� CRT ȫ�� locale �� iostream locale ��ͻ, ��Ҫͬʱʹ��
    _tsetlocale(LC_ALL, _T(""));

    // NOTE:
    // ����Ӧ������ѡ���ע����, ͨ������Ϊ������˾, ��֯, �Ŷӵ�����
    // �ú����趨 m_pszRegistryKey, ��Ӱ�� GetProfileInt �Ⱥ���
    // ����Ӧ�����õ�ע����:
    // HKCU\Software\<company name>\<application name>\<section name>\<value name>
    // ����ʹ��ע����ʹ�� ini �ļ�ʱ, ��ȥ�� SetRegistryKey
    SetRegistryKey(_T(MODULE_NAME));

    try {
        CMainFrame* pFrmWnd = new CMainFrame();

        // �ɹ�����Դ IDR_MAINFRAME ��������ܴ���, IDR_MAINFRAME ��ͬʱ��ʶ: �˵�(����), ��ݼ�, ��ͼ��, �������ַ���
        pFrmWnd->LoadFrame(IDR_MAINFRAME);

        // ���´�����ʾ
        pFrmWnd->ShowWindow(m_nCmdShow);
        pFrmWnd->UpdateWindow();

        m_pMainWnd = pFrmWnd;
    }
    catch (std::exception& e) {
        SHOWBMP_TRACEA("std::exception: what: %s, type: %s", e.what(), typeid(e).name());
        return FALSE;
    }
    catch (...) {
        SHOWBMP_TRACE("unknown exception");
        return FALSE;
    }

    return TRUE;
}

// NOTE: ���� ExitInstance ǰ, m_pMainWnd ���ڶ����ѱ��ͷŵ���
int CShowBmpApp::ExitInstance()
{
    // �ָ��ɵĹ���Ŀ¼
    _tchdir(m_OldWorkDir);
    return CWinApp::ExitInstance();
}

BOOL CShowBmpApp::InitModulePath(DWORD size)
{
    TCHAR* buf = new TCHAR[size];
    DWORD ret = GetModuleFileName(m_hInstance, buf, size);
    if (ret == 0) {
        SHOWBMP_TRACE("GetModuleFileName failed: %lu", GetLastError());
        delete[] buf;
        return FALSE;
    }
    m_ModulePath = buf;
    delete[] buf;
    return TRUE;
}

BOOL CShowBmpApp::InitWorkDir(const _TCHAR* dir)
{
    _TCHAR* oldDir = _tgetcwd(0, 0);
    if (oldDir == 0)
        return FALSE;
    m_OldWorkDir = oldDir;
    free(oldDir);
    return (_tchdir(dir) == 0);
}

CString CShowBmpApp::GetModuleDir() const
{
    int i = m_ModulePath.ReverseFind(_T('\\'));
    // û�ҵ� '\' ʱ, ���� ""
    if (i == -1)
        return _T("");
    return m_ModulePath.Left(i + 1);
}
