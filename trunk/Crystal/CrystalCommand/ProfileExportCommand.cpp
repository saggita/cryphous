#include "ProfileExportCommand.h"

#include "StringMarshaler.h"

#include "../CrystalPhysics/Profiler.h"

#include <fstream>

using namespace Crystal::Physics;
using namespace Crystal::Command;

ProfileExportCommand::ProfileExportCommand(ExportSettingCommand^ exportSettingCommand):
ExportCommandBase( exportSettingCommand)
{
}

void ProfileExportCommand::exportToFile( System::String^ fileName )
{
	const std::string& outputName = StringMarshaler::ToStdString( fileName );
	std::ofstream stream( outputName, std::ios::out | std::ios::app );
	std::map< std::string, double>& strAndTimes = Profiler::get()->getStrAndTimes();
	for( std::map< std::string, double>::const_iterator iter = strAndTimes.begin(); iter != strAndTimes.end(); ++iter ) {
		stream << iter->second << ",";
	}
	stream << std::endl;
}
