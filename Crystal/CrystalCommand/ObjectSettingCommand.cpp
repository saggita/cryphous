#include "ObjectSettingCommand.h"

#include "../CrystalPhysics/PhysicsObjectFactory.h"
#include "../CrystalPhysics/PhysicsObjectCondition.h"
#include "../CrystalGeom/Vector3d.h"
#include "../CrystalGeom/Box.h"
#include "../CrystalPhysics/SimulationSetting.h"

#include "ApplicationSettings.h"
#include "ParticleMarshaler.h"

#include <boost/foreach.hpp>

using namespace Crystal::Geom;
using namespace Crystal::Physics;
using namespace Crystal::Command;

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Diagnostics;
using namespace System::IO;
using namespace System::Xml;

ObjectSettingCommand::ObjectSettingCommand()
{
}

ObjectSettingCommand::~ObjectSettingCommand()
{
}

void ObjectSettingCommand::displaySettings()
{
	view->Rows->Clear();

	std::list<PhysicsObjectCondition>& conditions = *(ApplicationSettings::get()->conditions);

	for( std::list<PhysicsObjectCondition>::iterator iter = conditions.begin();
		iter != conditions.end(); ++iter ) {
		const PhysicsObjectCondition& condition = *(iter);
		
		String^ type = "";
		switch( condition.getObjectType() ) {
			case PhysicsObjectCondition::Fluid :
				type = "Fluid";
				break;
			case PhysicsObjectCondition::Rigid :
				type = "Obstacle";
				break;
			case PhysicsObjectCondition::RigidTwoWay :
				type = "Rigid";
				break;
			default:
				System::Diagnostics::Debug::Assert( false );
		}

		array<Object^>^ rowData = {
			type,
			condition.getPressureCoefficient(),
			condition.getViscosityCoefficient(),
			condition.getDensity()
		};
		
		view->Rows->Add( rowData );
	}
}

void ObjectSettingCommand::saveSettings()
{
	ApplicationSettings::get()->conditions->clear();
	ApplicationSettings::get()->factory->init();
	const Box& box = ApplicationSettings::get()->simulationSetting->boundaryBox;

	const double length = ApplicationSettings::get()->simulationSetting->particleDiameter;
	const double margin = 1.0e-12;

	for each( DataGridViewRow^ row in view->Rows ) {
		PhysicsObjectCondition::ObjectType objectType = PhysicsObjectCondition::Fluid;
		Debug::WriteLine( row->Cells[0]->Value->ToString() );
		if(  row->Cells[0]->Value->ToString() == "Fluid") {
			objectType = PhysicsObjectCondition::Fluid;
		}
		else if( row->Cells[0]->Value->ToString() == "Obstacle" ) {
			objectType = PhysicsObjectCondition::Rigid;
		}
		else if( row->Cells[0]->Value->ToString() == "Rigid") {
			objectType = PhysicsObjectCondition::RigidTwoWay;
		}
		else{
			Debug::Assert( false );
		}

		const double pressureCoe = Convert::ToDouble( row->Cells[1]->Value );
		const double viscosityCoe = Convert::ToDouble( row->Cells[2]->Value );
		const double density = Convert::ToDouble( row->Cells[3]->Value );
		const double minX = Convert::ToDouble( row->Cells[4]->Value ) + length * 0.5 - margin;
		const double maxX = Convert::ToDouble( row->Cells[5]->Value ) - length * 0.5 + margin;
		const double minY = Convert::ToDouble( row->Cells[6]->Value ) + length * 0.5 - margin;
		const double maxY = Convert::ToDouble( row->Cells[7]->Value ) - length * 0.5 + margin;
		const double minZ = Convert::ToDouble( row->Cells[8]->Value ) + length * 0.5 - margin;
		const double maxZ = Convert::ToDouble( row->Cells[9]->Value ) - length * 0.5 + margin;

		std::vector<Vector3d> points;
		for( double x = minX; x < maxX; x+= length ) {
			for( double y = minY; y < maxY; y+= length ) {
				for( double z = minZ; z < maxZ; z += length ) {
					points.push_back( Vector3d( x, y, z ) );
				}
			}
		}

		PhysicsObjectCondition* condition = new PhysicsObjectCondition(
			points,
			density,
			pressureCoe,
			viscosityCoe,
			objectType
			);
		ApplicationSettings::get()->factory->createPhysicsObject( *condition,  *(ApplicationSettings::get()->simulationSetting) );
		ApplicationSettings::get()->conditions->push_back( *condition );
	}
}

void ObjectSettingCommand::addObject()
{
	array<Object^>^ rowData = {
		"Fluid",
		10000.0,
		2.0,
		1000.0, 
		-0.1, 0.1, 
		0.0, 0.5,
		-0.1, 0.1,
	};
	
	view->Rows->Add( rowData );
}

void ObjectSettingCommand::deleteObject()
{
	DataGridViewRow^ row = view->CurrentRow;

	if( row == nullptr ) {
		return;
	}

	view->Rows->Remove( row );
}

//void ObjectSettingCommand::saveSettings(System::Collections::Generic::List<ManagedPosition^>^ managedPositions)
//{
//	ApplicationSettings::get()->conditions->clear();
//	ApplicationSettings::get()->factory->init();
//
//	//for each( DataGridViewRow^ row in view->Rows ) {
//	//	PhysicsObjectCondition::ObjectType objectType = PhysicsObjectCondition::Fluid;
//	//	Debug::WriteLine( row->Cells[0]->Value->ToString() );
//	//	if(  row->Cells[0]->Value->ToString() == "Fluid") {
//	//		objectType = PhysicsObjectCondition::Fluid;
//	//	}
//	//	else if( row->Cells[0]->Value->ToString() == "Obstacle" ) {
//	//		objectType = PhysicsObjectCondition::Rigid;
//	//	}
//	//	else if( row->Cells[0]->Value->ToString() == "Rigid") {
//	//		objectType = PhysicsObjectCondition::RigidTwoWay;
//	//	}
//	//	else{
//	//		Debug::Assert( false );
//	//	}
//
//	//	const double pressureCoe = Convert::ToDouble( row->Cells[1]->Value );
//	//	const double viscosityCoe = Convert::ToDouble( row->Cells[2]->Value );
//	//	const double density = Convert::ToDouble( row->Cells[3]->Value );
//	//	const double minX = Convert::ToDouble( row->Cells[4]->Value );
//	//	const double maxX = Convert::ToDouble( row->Cells[5]->Value );
//	//	const double minY = Convert::ToDouble( row->Cells[6]->Value );
//	//	const double maxY = Convert::ToDouble( row->Cells[7]->Value );
//	//	const double minZ = Convert::ToDouble( row->Cells[8]->Value );
//	//	const double maxZ = Convert::ToDouble( row->Cells[9]->Value );
//
//
//	std::vector<Geom::Vector3d> nativePoints = ParticleMarshaler::convertToNative(managedPositions);
//
//	/*PhysicsObjectCondition* condition = new PhysicsObjectCondition(
//			Box( Crystal::Geom::Vector3d( minX, minY, minZ), Crystal::Geom::Vector3d( maxX, maxY, maxZ ) ),
//			density,
//			pressureCoe,
//			viscosityCoe,
//			objectType
//			);*/
//		ApplicationSettings::get()->factory->createPhysicsObject( *condition,  *(ApplicationSettings::get()->simulationSetting) );
//		ApplicationSettings::get()->conditions->push_back( *condition );
//	}
//}