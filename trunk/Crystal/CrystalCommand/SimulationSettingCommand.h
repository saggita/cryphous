#pragma once

#include "DialogCommand.h"

namespace Crystal{
	namespace Command{

public ref class SimulationSettingCommand : public DialogCommand
{
public:
	SimulationSettingCommand(void);

	void setTextBox(
			System::Windows::Forms::TextBox^  textBoxTimeStep,
			System::Windows::Forms::TextBox^  textBoxEffectLength
		);
};
	}
}