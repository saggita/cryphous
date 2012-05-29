#pragma once

#include <string>

namespace Crystal{
	namespace Command{

public ref class StringMarshaler
{
public:
	static std::string ToStdString(System::String^ src);

	//static std::wstring ToStdWString(System::String^ src);
};

	}
}