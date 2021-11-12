// HiThrereWriterCLI.h
//

#pragma once

using namespace System;
using namespace System::Windows::Forms;

namespace HeadFirst {
namespace CppCLI {
namespace Leftover2 {

public ref class HiThrereWriterCLI {
public:
    HiThrereWriterCLI() {};

    static void HiThere(String^ name);
    static size_t ComputeLength(String^ str);
};

}
}
}
