// BuoyInfo.h
//

#pragma once

////////////////////////////////////////////////////////////////////////////////
// ȫ����
////////////////////////////////////////////////////////////////////////////////

// ģ����
const char      MODULE_NAMEA[]  = "BuoyInfo";
const wchar_t   MODULE_NAMEW[]  = L"BuoyInfo";
const _TCHAR    MODULE_NAME[]   = _T("BuoyInfo");

// ���û�������С
const int BUF_SIZE = 512;

// errno ���û�����ֵ����
const int ERR_USER = 128;

////////////////////////////////////////////////////////////////////////////////
// ���Թ���
////////////////////////////////////////////////////////////////////////////////

// �� "ģ����!������:" ��ʽ������Ա���
#define FMT(fmt)    SIMP_RPTFMT(fmt), MODULE_NAME
#define FMTA(fmt)   SIMP_RPTFMTA(fmt), MODULE_NAMEA

#define MY_RPT(rptType, fmt, ...)   SIMP_FMTRPT(MODULE_NAME, rptType, fmt, __VA_ARGS__)
#define MY_RPTA(rptType, fmt, ...)  SIMP_FMTRPTA(MODULE_NAMEA, rptType, fmt, __VA_ARGS__)

// ��ӡ������
#define PRINT_FILE          stdout
#define PRINT_FUNC          _ftprintf(PRINT_FILE, _T("----- : %s\n"), _T(__FUNCTION__))
#define PRINT_FUNC_BEGIN    _ftprintf(PRINT_FILE, _T("----- BEGIN: %s\n"), _T(__FUNCTION__))
#define PRINT_FUNC_END      _ftprintf(PRINT_FILE, _T("-----   END: %s\n"), _T(__FUNCTION__))
