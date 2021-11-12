////////////////////////////////////////////////////////////////////////////////
// 文    件 : ShowBmp.cpp
// 功能说明 :
//   程序的入口和初始化
//   ShowBmp 是 MFC 单窗口程序工程模板, 无 Doc/View 模型
//
// 版    本 : 1.0
// 作    者 : Breaker Zhao <breaker.zy_AT_gmail>
// 日    期 : 2010-10
////////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "ShowBmp.h"
#include "ClientView.h"
#include "MainFrame.h"

////////////////////////////////////////////////////////////////////////////////
// 全局量
////////////////////////////////////////////////////////////////////////////////

// 应用程序实例
CShowBmpApp g_ShowBmpApp;

////////////////////////////////////////////////////////////////////////////////
// 应用程序类 CShowBmpApp
////////////////////////////////////////////////////////////////////////////////

BOOL CShowBmpApp::InitInstance()
{
    CWinApp::InitInstance();

    // 如果装配文件 (manifest) 中指定使用 Windows 通用控件 ComCtl32.dll 6.0+ 版本, 则在 Windows XP 下需要调用 InitCommonControlsEx(), 否则窗口创建将失败
    // 设置程序中能够使用的通用控件类, ICC_WIN95_CLASSES 表示所有 Win95 通用控件
    INITCOMMONCONTROLSEX initCtrls;
    initCtrls.dwSize = sizeof(initCtrls);
    initCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&initCtrls);

    // 计算主模块全路径, 设置工作目录
    InitModulePath(MAX_PATH);
    InitWorkDir(GetModuleDir());

    // 设置 CRT locale, VC 2005 中 CRT 全局 locale 和 iostream locale 冲突, 不要同时使用
    _tsetlocale(LC_ALL, _T(""));

    // NOTE:
    // 保存应用设置选项的注册表键, 通常命名为开发公司, 组织, 团队的名字
    // 该函数设定 m_pszRegistryKey, 并影响 GetProfileInt 等函数
    // 保存应用设置的注册表键:
    // HKCU\Software\<company name>\<application name>\<section name>\<value name>
    // 当不使用注册表而使用 ini 文件时, 请去掉 SetRegistryKey
    SetRegistryKey(_T(MODULE_NAME));

    try {
        CMainFrame* pFrmWnd = new CMainFrame();

        // 由共享资源 IDR_MAINFRAME 创建主框架窗口, IDR_MAINFRAME 可同时标识: 菜单(必需), 快捷键, 主图标, 标题栏字符串
        pFrmWnd->LoadFrame(IDR_MAINFRAME);

        // 更新窗口显示
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

// NOTE: 进入 ExitInstance 前, m_pMainWnd 窗口对象已被释放掉了
int CShowBmpApp::ExitInstance()
{
    // 恢复旧的工作目录
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
    // 没找到 '\' 时, 返回 ""
    if (i == -1)
        return _T("");
    return m_ModulePath.Left(i + 1);
}
