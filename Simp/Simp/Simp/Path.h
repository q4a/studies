////////////////////////////////////////////////////////////////////////////////
// 文    件 : Path.h
// 功能说明 :
//   路径处理
//
// 版    本 : 1.0
// 作    者 : Breaker Zhao <breaker.zy_AT_gmail>
// 日    期 : 2011-10
// 授权许可 : Microsoft Public License <http://www.microsoft.com/en-us/openness/licenses.aspx#MPL>
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <Simp/Depends.h>
#include <Simp/Defs.h>

SIMP_NS_BEGIN

////////////////////////////////////////////////////////////////////////////////
// 路径操作
////////////////////////////////////////////////////////////////////////////////

// 得到模块所在的目录全路径, 以 '\' 结尾
inline
BOOL GetModuleDir(HMODULE module, __out _TCHAR* dir, size_t sizeDir, _TCHAR dirDelim = _T('\\')) {
    if (dir == NULL || sizeDir == 0)
        return FALSE;

    DWORD len = GetModuleFileName(module, dir, (DWORD) sizeDir);

    // =0 错误
    // =size_dir, 缓冲区太小路径被截断
    if (len == 0 || len == sizeDir)
        return FALSE;

    // 去掉 path 中 '\' 之后的部分
    _TCHAR* bslash = _tcsrchr(dir, dirDelim);

    // 路径中应该有 '\'
    if (bslash == NULL)
        return FALSE;

    // 如果 '\' 不是缓冲区中最后一个位置
    if (bslash != dir + sizeDir - 1)
        *(bslash + 1) = _T('\0');

    return TRUE;
}

SIMP_NS_END
