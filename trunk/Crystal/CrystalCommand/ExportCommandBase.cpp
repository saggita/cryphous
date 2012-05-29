#include "ExportCommandBase.h"

#include "ExportSettingCommand.h"

using namespace Crystal::Command;

ExportCommandBase::ExportCommandBase(ExportSettingCommand^ exportSettingCommand)
{
	this->exportSettingCommand = exportSettingCommand;
}

void ExportCommandBase::exportToFile(int step)
{
	if( !exportSettingCommand->isSaveTimeStep( step ) ) {
		return;
	}
	step += 1000;
	System::String^ imageFileName = exportSettingCommand->getBaseFileName() + step.ToString() + "." + exportSettingCommand->getExtension();
	exportToFile( imageFileName );
}