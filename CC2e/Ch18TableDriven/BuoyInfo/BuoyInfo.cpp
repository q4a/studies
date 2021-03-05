// BuoyInfo.cpp
//

#include "StdAfx.h"
#include "BuoyInfo.h"

#include "BuoyMsg.h"

////////////////////////////////////////////////////////////////////////////////
// ȫ����
////////////////////////////////////////////////////////////////////////////////

// ԭ���Ĺ���Ŀ¼
_TCHAR* OldWorkDir;

////////////////////////////////////////////////////////////////////////////////
// ��ʼ��������
////////////////////////////////////////////////////////////////////////////////

void Init();
void Uninit();

////////////////////////////////////////////////////////////////////////////////
// �������
////////////////////////////////////////////////////////////////////////////////

int _tmain(int argc, _TCHAR* argv[]) {
    Init();

    TestMsgDescTbl(FALSE);
    TestMsgTbl(TRUE);

    Uninit();
    _putts(_T("Press any key to Exit."));
    _gettch();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
// ��ʼ��������
////////////////////////////////////////////////////////////////////////////////

// ��ʼ�����л���
void Init() {
#define _USE_CRT_LOCALE

#if _MSC_VER > 1400
#define _USE_IOS_LOCALE
#endif

// CRT ȫ�� locale �� iostream imbue locale ��ͻ
// VC 2005 ���� (_MSC_VER = 1400)
// VC 2010 ���� (_MSC_VER = 1600)
#if _MSC_VER <= 1400 && defined(_USE_CRT_LOCALE) && defined(_USE_IOS_LOCALE)
#error cannot use CRT global locale and iostream imbue locale at the same time, when _MSC_VER <= 1400
#endif

#ifdef _USE_CRT_LOCALE
    _tsetlocale(LC_ALL, _T(""));
#endif

#ifdef _USE_IOS_LOCALE
    // ���� C++ iostream ��׼ IO �� locale
    std::locale loc(std::locale(""), std::locale::classic(), std::locale::numeric);
    tcout.imbue(loc);
    tcerr.imbue(loc);
    tcin.imbue(loc);
#endif

    // ���� CRT �������
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_WNDW);

    // ���õ�ǰ exe �ļ���Ŀ¼Ϊ����Ŀ¼
    _TCHAR modDir[BUF_SIZE];
    OldWorkDir = _tgetcwd(NULL, 0);
    Simp::GetModuleDir(GetModuleHandle(NULL), modDir, BUF_SIZE);
    _tchdir(modDir);
}

// �������л���
void Uninit() {
    // �ָ�ԭ���Ĺ���Ŀ¼
    _tchdir(OldWorkDir);
    free(OldWorkDir);

    // ��Ϊ��̬������ Uninit ֮������, �������¾�֮ǰ��Ҫ�ֹ��ͷź���̬�洢�ľ�̬����, �����������
    _CrtDumpMemoryLeaks();
}
