#include "SimulationSettingCommand.h"
#include "ApplicationSettings.h"

#include "../CrystalPhysics/SimulationSetting.h"

using namespace Crystal::Physics;
using namespace Crystal::Command;

using namespace System;
using namespace System::Windows::Forms;

SimulationSettingCommand::SimulationSettingCommand( ApplicationSettings^ settings)
{
	this->settings = settings;
}

void SimulationSettingCommand::setTextBox(System::Windows::Forms::TextBox ^textBoxTimeStep, System::Windows::Forms::TextBox ^textBoxEffectLength )
{
	SimulationSetting* setting = settings->simulationSetting;

	itemAndVariables.Clear();
	itemAndVariables.Push( gcnew FloatTextBox( &(setting->timeStep), textBoxTimeStep ) );
	itemAndVariables.Push( gcnew FloatTextBox( &(setting->particleDiameter), textBoxEffectLength ) );
}