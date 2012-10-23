// Common.h
//

#pragma once

#include "Common/User.h"

////////////////////////////////////////////////////////////////////////////////
// Ëæ»úÊý
////////////////////////////////////////////////////////////////////////////////

inline void InitRand() {
    srand((unsigned) time(NULL));
}

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
// ×Ö·û´®¸¨Öú
////////////////////////////////////////////////////////////////////////////////

inline void DumpString(const _TCHAR* prompt, const _TCHAR* str) {
    _tprintf(_T("----- %s BEGIN -----\n"), prompt);
    _putts(str);
    _tprintf(_T("----- %s END   -----\n"), prompt);
}

////////////////////////////////////////////////////////////////////////////////
// Ê±ÖÓ
////////////////////////////////////////////////////////////////////////////////

inline UINT64 CPUClock() {
    return __rdtsc();
}

inline UINT64 CRTClock() {
    return clock();
}
