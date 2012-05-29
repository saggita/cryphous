#pragma once

#include "ExportCommandBase.h"

namespace Crystal{
	namespace Command{
		ref class ExportSettingCommand;

public ref class ProfileExportCommand : public ExportCommandBase
{
public:
	ProfileExportCommand(ExportSettingCommand^ exportSettingCommand);

protected:
	virtual void exportToFile(System::String^ fileName) override;
};

	}
}