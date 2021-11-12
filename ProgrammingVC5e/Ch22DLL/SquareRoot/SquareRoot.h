// SquareRoot.h : main header file for the SquareRoot DLL
//

#pragma once

#ifndef __AFXWIN_H__
#error "include 'StdAfx.h' before including this file for PCH"
#endif

#include "Resource.h"		// main symbols

#ifdef _SQUAREROOT_EXPORT
#define SQUAREROOT_API __declspec(dllexport)
#else
#define SQUAREROOT_API __declspec(dllimport)
#endif  // SQUAREROOT_EXPORT

////////////////////////////////////////////////////////////////////////////////
// ȫ����
////////////////////////////////////////////////////////////////////////////////

#ifdef _SQUAREROOT_EXPORT
#undef MODULE_NAME
#define MODULE_NAME     "SquareRoot"    // ����ģ����
#endif

////////////////////////////////////////////////////////////////////////////////
// ���Թ���
////////////////////////////////////////////////////////////////////////////////

#ifdef _SQUAREROOT_EXPORT

// �� "ģ����!������:" ��ʽ������Ա���
#define FMT(fmt)    _T(MODULE_NAME) _T("!") _T(__FUNCTION__) _T(": ")  _T(fmt) _T("\n")
#define FMTA(fmt)   MODULE_NAME "!" __FUNCTION__ ": " fmt "\n"

#define MYTRACE(fmt, ...)   TRACE(FMT(fmt), __VA_ARGS__)
#define MYTRACEA(fmt, ...)  TRACE(FMTA(fmt), __VA_ARGS__)

#endif  // _SQUAREROOT_EXPORT

// CSquareRootApp
// See SquareRoot.cpp for the implementation of this class
//

class CSquareRootApp : public CWinApp {
public:
    CSquareRootApp();

// Overrides
public:
    virtual BOOL InitInstance();

    DECLARE_MESSAGE_MAP()
};

SQUAREROOT_API double SquareRoot(double num);
