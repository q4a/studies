// ContextMenu1.h
//

#ifndef __CONTEXTMENU1_H__
#define __CONTEXTMENU1_H__

// 资源 ID 符号常量
#include "res/Resource.h"

////////////////////////////////////////////////////////////////////////////////
// 应用程序类 CContextMenu1App
////////////////////////////////////////////////////////////////////////////////

class CContextMenu1App : public CWinApp {
public:
    CContextMenu1App() {}

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
// 全局设置
////////////////////////////////////////////////////////////////////////////////

#undef MODULE_NAME
#define MODULE_NAME     "ContextMenu1"  // 程序模块名

#define BUF_SIZE        256 // 常用缓冲区大小

#define DEFAULT_WIDTH   800 // 主窗口默认宽度
#define DEFAULT_HEIGHT  600 // 主窗口默认高度

extern CContextMenu1App ContextMenu1App;    // 应用程序实例

////////////////////////////////////////////////////////////////////////////////
// 调试功能
////////////////////////////////////////////////////////////////////////////////

// Debug 版 new
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 以 "模块名!函数名:" 形式输出调试报告
#define FMT(fmt)                _T(MODULE_NAME) _T("!") _T(__FUNCTION__) _T(": ")  _T(fmt) _T("\n")
#define FMTA(fmt)               MODULE_NAME "!" __FUNCTION__ ": " fmt "\n"

#define MYTRACE(fmt, ...)       TRACE(FMT(fmt), __VA_ARGS__)
#define MYTRACEA(fmt, ...)      TRACE(FMTA(fmt), __VA_ARGS__)

#define TRACE_FAIL(func, err)   MYTRACE("%s failed: %ld", _T(func), err)
#define TRACE_FAILA(func, err)  MYTRACEA("%s failed: %ld", func, err)

#define FAILED_DO(hr, exp)      if (FAILED(hr)) { exp; }

#endif  // __CONTEXTMENU1_H__
