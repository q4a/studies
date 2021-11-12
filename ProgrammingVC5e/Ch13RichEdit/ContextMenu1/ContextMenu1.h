// ContextMenu1.h
//

#ifndef __CONTEXTMENU1_H__
#define __CONTEXTMENU1_H__

// ��Դ ID ���ų���
#include "res/Resource.h"

////////////////////////////////////////////////////////////////////////////////
// Ӧ�ó����� CContextMenu1App
////////////////////////////////////////////////////////////////////////////////

class CContextMenu1App : public CWinApp {
public:
    CContextMenu1App() {}

public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();

public:
    // �õ�������ģ��ȫ·��
    const CString& GetModulePath() const {
        return m_ModulePath;
    }
    CString GetModuleDir() const;       // ȡ������������Ŀ¼ȫ·��

private:
    BOOL InitModulePath(DWORD size);    // ����������ģ���ȫ·�� m_ModulePath
    BOOL InitWorkDir(const _TCHAR* dir);// ���ù���Ŀ¼

private:
    CString m_ModulePath;               // ������ģ���ȫ·��
    CString m_OldWorkDir;               // �ɵĹ���Ŀ¼
};

////////////////////////////////////////////////////////////////////////////////
// ȫ������
////////////////////////////////////////////////////////////////////////////////

#undef MODULE_NAME
#define MODULE_NAME     "ContextMenu1"  // ����ģ����

#define BUF_SIZE        256 // ���û�������С

#define DEFAULT_WIDTH   800 // ������Ĭ�Ͽ��
#define DEFAULT_HEIGHT  600 // ������Ĭ�ϸ߶�

extern CContextMenu1App ContextMenu1App;    // Ӧ�ó���ʵ��

////////////////////////////////////////////////////////////////////////////////
// ���Թ���
////////////////////////////////////////////////////////////////////////////////

// Debug �� new
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// �� "ģ����!������:" ��ʽ������Ա���
#define FMT(fmt)                _T(MODULE_NAME) _T("!") _T(__FUNCTION__) _T(": ")  _T(fmt) _T("\n")
#define FMTA(fmt)               MODULE_NAME "!" __FUNCTION__ ": " fmt "\n"

#define MYTRACE(fmt, ...)       TRACE(FMT(fmt), __VA_ARGS__)
#define MYTRACEA(fmt, ...)      TRACE(FMTA(fmt), __VA_ARGS__)

#define TRACE_FAIL(func, err)   MYTRACE("%s failed: %ld", _T(func), err)
#define TRACE_FAILA(func, err)  MYTRACEA("%s failed: %ld", func, err)

#define FAILED_DO(hr, exp)      if (FAILED(hr)) { exp; }

#endif  // __CONTEXTMENU1_H__
