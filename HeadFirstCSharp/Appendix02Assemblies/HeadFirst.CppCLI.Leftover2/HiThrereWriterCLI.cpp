// HiThrereWriterCLI.cpp
//

#include "StdAfx.h"
#include "HiThrereWriterCLI.h"
#include "Compute.h"

namespace HeadFirst {
namespace CppCLI {
namespace Leftover2 {

void HiThrereWriterCLI::HiThere(String^ name) {
    MessageBox::Show("[CLI] Hi there! My name is " + name);
}

size_t HiThrereWriterCLI::ComputeLength(String^ str) {
    return Compute::StringLength((_TCHAR*) System::Runtime::InteropServices::Marshal::StringToHGlobalAuto(str).ToPointer());
}

}
}
}
