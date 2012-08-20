#include "GraphicsSettingCommand.h"

#include "ApplicationSettings.h"
#include "../CrystalGraphics/GraphicsSettings.h"

using namespace Crystal::Command;
using namespace Crystal::Graphics;

using namespace System;
using namespace System::Windows::Forms;

GraphicsSettingCommand::GraphicsSettingCommand() :
DialogCommand(){
}

GraphicsSettingCommand::~GraphicsSettingCommand(){
}

void GraphicsSettingCommand::setTrackBar(
		System::Windows::Forms::TrackBar^ trackBarPointSize,
		System::Windows::Forms::TrackBar^ trackBarAlphaPower,
		System::Windows::Forms::CheckBox^ checkBoxBoundingBox,
		System::Windows::Forms::CheckBox^ doDisplaySurface
		)
{
	itemAndVariables.Clear();

	GraphicsSettings* graphicsSettings = ApplicationSettings::get()->graphicsSettings;

	itemAndVariables.Push( gcnew IntTrackBar( &(graphicsSettings->pointSize), trackBarPointSize) );
	itemAndVariables.Push( gcnew IntTrackBar( &(graphicsSettings->pointAlpha), trackBarAlphaPower ) );
	itemAndVariables.Push( gcnew BoolCheckBox( &(graphicsSettings->drawBoundingBox), checkBoxBoundingBox ) );
	itemAndVariables.Push( gcnew BoolCheckBox( &(graphicsSettings->doDisplaySurface), doDisplaySurface ) );
}