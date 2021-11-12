// StdStream.cpp
//
// MSVC options:
// CXXFLAGS = /nologo /MD /W3 /O2 /Oi /D "WIN32" /D "NDEBUG" /c /Gm /Zi /Yu"StdAfx.h"
//

#include <StdAfx.h>

////////////////////////////////////////////////////////////////////////////////
// Get stdio streams
////////////////////////////////////////////////////////////////////////////////

extern "C" {
FILE* get_stdin()   { return stdin; }
FILE* get_stdout()  { return stdout; }
FILE* get_stderr()  { return stderr; }
}
