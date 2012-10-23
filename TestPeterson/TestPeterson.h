// TestPeterson.h
//

#pragma once

////////////////////////////////////////////////////////////////////////////////
// 全局量
////////////////////////////////////////////////////////////////////////////////

// 模块名
const char      MODULE_NAMEA[]  = "SimpProj";
const wchar_t   MODULE_NAMEW[]  = L"SimpProj";
const _TCHAR    MODULE_NAME[]   = _T("SimpProj");

// 常用缓冲区大小
const int BUF_SIZE = 256;

// 日志对象
extern Simp::LogBase<char>*     LogA;
extern Simp::LogBase<wchar_t>*  LogW;
extern Simp::LogBase<_TCHAR>*   Log;

////////////////////////////////////////////////////////////////////////////////
// 调试功能
////////////////////////////////////////////////////////////////////////////////

// 以 "模块名!函数名:" 形式输出调试报告
#define FMT(fmt)    SIMP_RPTFMT(fmt), MODULE_NAME
#define FMTA(fmt)   SIMP_RPTFMTA(fmt), MODULE_NAMEA

#define MY_RPT(rptType, fmt, ...)   SIMP_FMTRPT(MODULE_NAME, rptType, fmt, __VA_ARGS__)
#define MY_RPTA(rptType, fmt, ...)  SIMP_FMTRPTA(MODULE_NAMEA, rptType, fmt, __VA_ARGS__)

// 打印函数名
#define PRINT_FILE          stdout
#define PRINT_FUNC          _ftprintf(PRINT_FILE, _T("----- : %s\n"), _T(__FUNCTION__))
#define PRINT_FUNC_BEGIN    _ftprintf(PRINT_FILE, _T("----- BEGIN: %s\n"), _T(__FUNCTION__))
#define PRINT_FUNC_END      _ftprintf(PRINT_FILE, _T("-----   END: %s\n"), _T(__FUNCTION__))
