#pragma once

#include "ExportCommandBase.h"

namespace Crystal{
	namespace Command{
		ref class ExportSettingCommand;

public ref class ParticleExportCommand : public ExportCommandBase
{
public:
	ParticleExportCommand(ExportSettingCommand^ exportSettingCommand);

protected:
	virtual void exportToFile( System::String^ path ) override;
};

	}
}