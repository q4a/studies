// Common.h
//

#pragma once

#include "Common/User.h"

////////////////////////////////////////////////////////////////////////////////
// 随机数
////////////////////////////////////////////////////////////////////////////////

// [min, max)
inline int RandInt(int min, int max) {
    return (int) ((double) rand() / (RAND_MAX + 1) * (max - min) + min);
}

inline void RandString(__out _TCHAR* str, size_t size, _TCHAR min, _TCHAR max) {
    _ASSERTE(str != NULL);
    size_t i = 0;
    for (; i < size; i++)
        str[i] = RandInt(min, max);
    str[size - 1] = 0;
}

////////////////////////////////////////////////////////////////////////////////
// 字符串辅助
////////////////////////////////////////////////////////////////////////////////

inline void DumpString(const _TCHAR* prompt, const _TCHAR* str) {
    _tprintf(_T("----- %s BEGIN -----\n"), prompt);
    _putts(str);
    _tprintf(_T("----- %s END   -----\n"), prompt);
}

////////////////////////////////////////////////////////////////////////////////
// 时钟
////////////////////////////////////////////////////////////////////////////////

inline UINT64 CPUClock() {
    return __rdtsc();
}

// 数据量小时内存拷贝很快，CRTClock 识别不到差值
inline UINT64 CRTClock() {
    return clock();
}
