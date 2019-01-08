// StrHelper.cpp
//
// MSVC options:
// CXXFLAGS = /nologo /MD /W3 /O2 /Oi /D "WIN32" /D "NDEBUG" /c /Gm /Zi /Yu"StdAfx.h"
//

#include <StdAfx.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// C-style string trim
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern "C" {

char* rtrim(_Inout_ char* str)
{
    char* trail = NULL;
    for (char* p = str; *p != 0; ++p) {
        if (!isspace(*p))
            trail = NULL;
        else if (trail == NULL)
            trail = p;
    }
    if (trail != NULL)
        *trail = 0;
    return str;
}

char* ltrim(_Inout_ char* str)
{
    char* dst = str;
    while (isspace(*str))
        ++str;
    strcpy(dst, str);
    return dst;
}

char* trim(_Inout_ char* str)
{
    return ltrim(rtrim(str));
}

}
