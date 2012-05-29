#include "SimulationSettingCommand.h"

#include "../CrystalPhysics/SimulationSetting.h"

using namespace Crystal::Physics;
using namespace Crystal::Command;

using namespace System;
using namespace System::Windows::Forms;

SimulationSettingCommand::SimulationSettingCommand(void)
{
}

void SimulationSettingCommand::setTextBox(System::Windows::Forms::TextBox ^textBoxTimeStep, System::Windows::Forms::TextBox ^textBoxEffectLength )
{
	SimulationSetting* setting = SimulationSetting::get();

	itemAndVariables.Clear();
	itemAndVariables.Push( gcnew DoubleTextBox( &(setting->timeStep), textBoxTimeStep ) );
	itemAndVariables.Push( gcnew DoubleTextBox( &(setting->effectLength), textBoxEffectLength ) );
}