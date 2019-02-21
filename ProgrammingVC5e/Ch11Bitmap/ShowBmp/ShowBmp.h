////////////////////////////////////////////////////////////////////////////////
// 文    件 : ShowBmp.h
// 功能说明 :
//   程序的入口和初始化
//
// 版    本 : 1.0
// 作    者 : Breaker Zhao <breaker.zy_AT_gmail>
// 日    期 : 2010-10
////////////////////////////////////////////////////////////////////////////////

#ifndef __SHOWBMP_H__
#define __SHOWBMP_H__

// 资源 ID 符号常量
#include "res/Resource.h"

////////////////////////////////////////////////////////////////////////////////
// 应用程序类 CShowBmpApp
////////////////////////////////////////////////////////////////////////////////

class CShowBmpApp : public CWinApp {
public:
    CShowBmpApp() {}

public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();

public:
    // 得到主程序模块全路径
    const CString& GetModulePath() const {
        return m_ModulePath;
    }
    CString GetModuleDir() const;       // 取得主程序所在目录全路径

private:
    BOOL InitModulePath(DWORD size);    // 计算主程序模块的全路径 m_ModulePath
    BOOL InitWorkDir(const _TCHAR* dir);// 设置工作目录

private:
    CString m_ModulePath;               // 主程序模块的全路径
    CString m_OldWorkDir;               // 旧的工作目录
};

////////////////////////////////////////////////////////////////////////////////
// 全局量
////////////////////////////////////////////////////////////////////////////////

#undef MODULE_NAME
#define MODULE_NAME         "ShowBmp"   // 程序模块名

#define BUF_SIZE            256         // 常用缓冲区大小

#define DEFAULT_VIEW_WIDTH  800         // 主窗口默认宽度
#define DEFAULT_VIEW_HEIGHT 600         // 主窗口默认高度

extern CShowBmpApp      g_ShowBmpApp;   // 应用程序实例

////////////////////////////////////////////////////////////////////////////////
// 调试功能
////////////////////////////////////////////////////////////////////////////////

// Debug 版 new
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define SHOWBMP_TRACE(fmt, ...)     \
    TRACE(_T(MODULE_NAME) _T("!") _T(__FUNCTION__) _T(": ") _T(fmt) _T("\n"), __VA_ARGS__)

#define SHOWBMP_TRACEA(fmt, ...)   \
    TRACE(MODULE_NAME "!" __FUNCTION__ ": " fmt "\n", __VA_ARGS__)

#endif  // __SHOWBMP_H__
