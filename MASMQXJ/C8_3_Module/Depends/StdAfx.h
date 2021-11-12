// StdAfx.h
//

#pragma once

////////////////////////////////////////////////////////////////////////////////
// Dependent Libraries
////////////////////////////////////////////////////////////////////////////////

// C Runtime Library (CRT)
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#if _MSC_VER >= 1400
// VS 2005 (MSVC 8.0)+
#include <sal.h>
#else
#define _In_
#define _Out_
#define _Inout_
#endif
