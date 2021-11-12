// Compute.h
//

#pragma once

#ifdef _MANAGED
#pragma managed(push, off)
#endif

namespace HeadFirst {
namespace CppCLI {
namespace Leftover2 {

class Compute {
private:
    Compute();

public:
    static size_t StringLength(const _TCHAR* str);
};

}
}
}

#ifdef _MANAGED
#pragma managed(pop)
#endif
