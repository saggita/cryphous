#include "ParticleExportCommand.h"

#include "StringMarshaler.h"
//#include "../CrystalGraphics/VisualParticleFactory.h"

//using namespace Crystal::Graphics;
using namespace Crystal::Command;

using namespace System;
using namespace System::Windows::Forms;

ParticleExportCommand::ParticleExportCommand(ExportSettingCommand^ exportSettingCommand) :
ExportCommandBase( exportSettingCommand)
{
}

void ParticleExportCommand::exportToFile(System::String ^path)
{
	//VisualParticleFactory::get()->writeToFile( StringMarshaler::ToStdString( path) );
}