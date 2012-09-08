#pragma once

#include "DialogCommand.h"

namespace Crystal{
	namespace Command{
		ref class ApplicationSettings;

public ref class GraphicsSettingCommand : public DialogCommand
{
public:
	GraphicsSettingCommand(ApplicationSettings^ settings);

	~GraphicsSettingCommand();

	void setTrackBar( 
		System::Windows::Forms::TrackBar^ trackBarPointSize,
		System::Windows::Forms::TrackBar^ trackBarAlphaPower,
		System::Windows::Forms::CheckBox^ checkBoxBoundingBox,
		System::Windows::Forms::CheckBox^ doDisplaySurface
		);

private:
	ApplicationSettings^ settings;
};

	}
}