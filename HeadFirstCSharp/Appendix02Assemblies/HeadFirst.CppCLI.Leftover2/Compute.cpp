// Compute.cpp
//

#include "StdAfx.h"
#include "Compute.h"

#ifdef _MANAGED
#pragma managed(push, off)
#endif

namespace HeadFirst {
namespace CppCLI {
namespace Leftover2 {

size_t Compute::StringLength(const _TCHAR* str) {
    return _tcslen(str);
}

}
}
}

#ifdef _MANAGED
#pragma managed(pop)
#endif

