#pragma once

namespace Crystal{
	namespace Command{
		ref class ExportSettingCommand;

public ref class ExportCommandBase abstract
{
public:
	ExportCommandBase(ExportSettingCommand^ exportImagesSettingCommand);

	virtual ~ExportCommandBase() {};

	void exportToFile( int step );

protected:
	virtual void exportToFile( System::String^ path ) = 0;

private:
	ExportSettingCommand^ exportSettingCommand;
};
	}
}