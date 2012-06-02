#include "ParticleExportCommand.h"

#include "StringMarshaler.h"
#include "ApplicationSettings.h"

#include "../CrystalPhysics/PhysicsObjectFactory.h"

using namespace Crystal::Physics;
using namespace Crystal::Command;

using namespace System;
using namespace System::Windows::Forms;

ParticleExportCommand::ParticleExportCommand(ExportSettingCommand^ exportSettingCommand) :
ExportCommandBase( exportSettingCommand)
{
}

void ParticleExportCommand::exportToFile(System::String ^path)
{
	ApplicationSettings::get()->factory->writeToFile( StringMarshaler::ToStdString( path ) );
}