////////////////////////////////////////////////////////////////////////////////
// ��    �� : ShowBmp.h
// ����˵�� :
//   �������ںͳ�ʼ��
//
// ��    �� : 1.0
// ��    �� : Breaker Zhao <breaker.zy_AT_gmail>
// ��    �� : 2010-10
////////////////////////////////////////////////////////////////////////////////

#ifndef __SHOWBMP_H__
#define __SHOWBMP_H__

// ��Դ ID ���ų���
#include "res/Resource.h"

////////////////////////////////////////////////////////////////////////////////
// Ӧ�ó����� CShowBmpApp
////////////////////////////////////////////////////////////////////////////////

class CShowBmpApp : public CWinApp {
public:
    CShowBmpApp() {}

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
#define MODULE_NAME         "ShowBmp"   // ����ģ����

#define BUF_SIZE            256         // ���û�������С

#define DEFAULT_VIEW_WIDTH  800         // ������Ĭ�Ͽ��
#define DEFAULT_VIEW_HEIGHT 600         // ������Ĭ�ϸ߶�

extern CShowBmpApp      g_ShowBmpApp;   // Ӧ�ó���ʵ��

////////////////////////////////////////////////////////////////////////////////
// ���Թ���
////////////////////////////////////////////////////////////////////////////////

// Debug �� new
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define SHOWBMP_TRACE(fmt, ...)     \
    TRACE(_T(MODULE_NAME) _T("!") _T(__FUNCTION__) _T(": ") _T(fmt) _T("\n"), __VA_ARGS__)

#define SHOWBMP_TRACEA(fmt, ...)   \
    TRACE(MODULE_NAME "!" __FUNCTION__ ": " fmt "\n", __VA_ARGS__)

#endif  // __SHOWBMP_H__
