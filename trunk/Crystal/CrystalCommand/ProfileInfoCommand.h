#pragma once

namespace Crystal{
	namespace Command{

public ref class ProfileInfoCommand
{
public:
	ProfileInfoCommand();

	void display( System::String^ productName, System::Windows::Forms::ListBox^ listBox );
};

	}
}
