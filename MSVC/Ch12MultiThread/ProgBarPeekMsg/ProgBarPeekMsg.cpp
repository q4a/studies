////////////////////////////////////////////////////////////////////////////////
// 文    件 : ProgBarPeekMsg.cpp
// 功能说明 :
//   程序的入口和初始化
//
// 版    本 : 1.0
// 作    者 : Breaker Zhao <breaker.zy_AT_gmail>
// 日    期 : 2010-10
////////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "ProgBarPeekMsg.h"
#include "ClientView.h"
#include "MainFrame.h"

////////////////////////////////////////////////////////////////////////////////
// 全局量
////////////////////////////////////////////////////////////////////////////////

// 应用程序实例
CProgBarPeekMsgApp g_ProgBarPeekMsgApp;

////////////////////////////////////////////////////////////////////////////////
// 应用程序类 CProgBarPeekMsgApp
////////////////////////////////////////////////////////////////////////////////

BOOL CProgBarPeekMsgApp::InitInstance()
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
        TRACE_ERRA("std::exception: what: %s, type: %s", e.what(), typeid(e).name());
        return FALSE;
    }
    catch (...) {
        TRACE_ERR("unknown exception");
        return FALSE;
    }

    return TRUE;
}

// NOTE: 进入 ExitInstance 前, m_pMainWnd 窗口对象已被释放掉了
int CProgBarPeekMsgApp::ExitInstance()
{
    // 恢复旧的工作目录
    _tchdir(m_OldWorkDir);
    return CWinApp::ExitInstance();
}

BOOL CProgBarPeekMsgApp::InitModulePath(DWORD size)
{
    TCHAR* buf = new TCHAR[size];
    DWORD ret = GetModuleFileName(m_hInstance, buf, size);
    if (ret == 0) {
        TRACE_ERR("GetModuleFileName failed: %lu", GetLastError());
        delete[] buf;
        return FALSE;
    }
    m_ModulePath = buf;
    delete[] buf;
    return TRUE;
}

BOOL CProgBarPeekMsgApp::InitWorkDir(const _TCHAR* dir)
{
    _TCHAR* oldDir = _tgetcwd(0, 0);
    if (oldDir == 0)
        return FALSE;
    m_OldWorkDir = oldDir;
    free(oldDir);
    return (_tchdir(dir) == 0);
}

CString CProgBarPeekMsgApp::GetModuleDir() const
{
    int i = m_ModulePath.ReverseFind(_T('\\'));
    return (i == -1 ? _T("") : m_ModulePath.Left(i + 1));   // 没找到 '\' 时, 返回 ""
}
