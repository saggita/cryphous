#pragma once

namespace Crystal{
	namespace Command{

public ref class BoundarySettingCommand
{
public:
	BoundarySettingCommand(void);

	void displayBoundarySetting(System::Windows::Forms::DataGridView^ view);

	void saveBoundarySetting(System::Windows::Forms::DataGridView^ view);
};

	}
}