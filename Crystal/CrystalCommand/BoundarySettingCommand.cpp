#include "BoundarySettingCommand.h"
#include "ApplicationSettings.h"

#include "../CrystalPhysics/SimulationSetting.h"

#include "../CrystalGeom/Box.h"
#include "../CrystalGeom/Vector3d.h"

using namespace Crystal::Geom;
using namespace Crystal::Physics;
using namespace Crystal::Command;

using namespace System;

BoundarySettingCommand::BoundarySettingCommand(void)
{
}

void BoundarySettingCommand::displayBoundarySetting(System::Windows::Forms::DataGridView^ view)
{
	view->Rows->Clear();

	const Box& box = ApplicationSettings::get()->simulationSetting->boundaryBox;

	array<Object^>^ minData = {
		box.getMinX(), box.getMinY(), box.getMinZ()
	};
	view->Rows->Add( minData );

	array<Object^>^ maxData = {
		box.getMaxX(), box.getMaxY(), box.getMaxZ()
	};
	view->Rows->Add( maxData );
}

void BoundarySettingCommand::saveBoundarySetting(System::Windows::Forms::DataGridView^ view)
{
	const float minX = Convert::ToSingle( view->Rows[0]->Cells[0]->Value );
	const float minY = Convert::ToSingle( view->Rows[0]->Cells[1]->Value );
	const float minZ = Convert::ToSingle( view->Rows[0]->Cells[2]->Value );

	const float maxX = Convert::ToSingle( view->Rows[1]->Cells[0]->Value );
	const float maxY = Convert::ToSingle( view->Rows[1]->Cells[1]->Value );
	const float maxZ = Convert::ToSingle( view->Rows[1]->Cells[2]->Value );

	 ApplicationSettings::get()->simulationSetting->boundaryBox = Box( Crystal::Geom::Vector3d( minX, minY, minZ), 
		Crystal::Geom::Vector3d( maxX, maxY, maxZ) );
}