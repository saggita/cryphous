#pragma once

#include "DialogCommand.h"
#include "ApplicationSettings.h"

namespace Crystal{
	namespace Command{

public ref class SimulationSettingCommand : public DialogCommand
{
public:
	SimulationSettingCommand(ApplicationSettings^ settings);

	void setTextBox(
			System::Windows::Forms::TextBox^  textBoxTimeStep,
			System::Windows::Forms::TextBox^  textBoxEffectLength
		);

private:
	ApplicationSettings^ settings;
};
	}
}