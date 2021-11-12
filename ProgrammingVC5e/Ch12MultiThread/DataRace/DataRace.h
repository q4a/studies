////////////////////////////////////////////////////////////////////////////////
// ��    �� : DataRace.h
// ����˵�� :
//   �������ںͳ�ʼ��
//
// ��    �� : 1.0
// ��    �� : Breaker Zhao <breaker.zy_AT_gmail>
// ��    �� : 2010-10
////////////////////////////////////////////////////////////////////////////////

#ifndef __DATARACE_H__
#define __DATARACE_H__

// ��Դ ID ���ų���
#include "res/Resource.h"

////////////////////////////////////////////////////////////////////////////////
// Ӧ�ó����� CDataRaceApp
////////////////////////////////////////////////////////////////////////////////

class CDataRaceApp : public CWinApp {
public:
    CDataRaceApp() {}

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
// ȫ����
////////////////////////////////////////////////////////////////////////////////

#undef MODULE_NAME
#define MODULE_NAME     "DataRace"   // ����ģ����

#define BUF_SIZE        256         // ���û�������С

#define DEFAULT_WIDTH   800         // ������Ĭ�Ͽ��
#define DEFAULT_HEIGHT  600         // ������Ĭ�ϸ߶�

extern CDataRaceApp      g_DataRaceApp;   // Ӧ�ó���ʵ��

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

#define TRACE_ERR(fmt, ...)     TRACE(FMT(fmt), __VA_ARGS__)
#define TRACE_ERRA(fmt, ...)    TRACE(FMTA(fmt), __VA_ARGS__)

#define TRACE_FAIL(func, err)   TRACE_ERR("%s failed: %ld", _T(func), err)
#define TRACE_FAILA(func, err)  TRACE_ERRA("%s failed: %ld", func, err)

#define FAILED_DO(hr, exp)      if (FAILED(hr)) { exp; }

#endif  // __DATARACE_H__
