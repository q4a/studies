// SimpTest.h
//

#pragma once

////////////////////////////////////////////////////////////////////////////////
// 全局量
////////////////////////////////////////////////////////////////////////////////

// 程序模块名
#undef MODULE_NAME
#define MODULE_NAME     "SimpTest"

// 常用缓冲区大小
#define BUF_SIZE        512

// 日志对象
extern Simp::LogBaseT<char>*    LogA;
extern Simp::LogBaseT<wchar_t>* LogW;
extern Simp::LogBaseT<_TCHAR>*  Log;

////////////////////////////////////////////////////////////////////////////////
// 调试功能
////////////////////////////////////////////////////////////////////////////////

// 以 "模块名!函数名:" 形式输出调试报告
#define FMT(fmt)    SIMP_RPTFMT(MODULE_NAME, fmt)
#define FMTA(fmt)   SIMP_RPTFMTA(MODULE_NAME, fmt)

#define MY_RPT(rptType, fmt, ...)   SIMP_FMTRPT(MODULE_NAME, rptType, fmt, __VA_ARGS__)
#define MY_RPTA(rptType, fmt, ...)  SIMP_FMTRPTA(MODULE_NAME, rptType, fmt, __VA_ARGS__)

// 打印函数名
#define PRINT_FILE          stdout
#define PRINT_FUNC          _ftprintf(PRINT_FILE, _T("----- : %s\n"), _T(__FUNCTION__))
#define PRINT_FUNC_BEGIN    _ftprintf(PRINT_FILE, _T("----- BEGIN: %s\n"), _T(__FUNCTION__))
#define PRINT_FUNC_END      _ftprintf(PRINT_FILE, _T("-----   END: %s\n"), _T(__FUNCTION__))

#define MY_CALL_RPT(rptType, ret, func, paramList)  SIMP_CALL_RPT(rptType, _T(MODULE_NAME) _T("!") _T(__FUNCTION__) _T(": "), ret, func, paramList)
