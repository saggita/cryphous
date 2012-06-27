
#include "StringMarshaler.h"

#include <string>
#include <iostream>
using namespace std;
using namespace System;

using namespace Crystal::Command;

string StringMarshaler::ToStdString( String ^ s ) {
   using namespace Runtime::InteropServices;
   const char* chars = 
      (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
   string os = chars;
   Marshal::FreeHGlobal(IntPtr((void*)chars));
   return os;
}
