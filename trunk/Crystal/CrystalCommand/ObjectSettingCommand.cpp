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

void ObjectSettingCommand::saveSettings(String^ type, const double density, const double pressureCoe, const double viscosityCoe, System::Collections::Generic::List<ManagedPosition^>^ managedPositions)
{
	std::vector<Geom::Vector3d> points = ParticleMarshaler::convertToNative(managedPositions);

	ApplicationSettings::get()->conditions->clear();
	ApplicationSettings::get()->factory->init();
	const Box& box = ApplicationSettings::get()->simulationSetting->boundaryBox;

	
	PhysicsObjectCondition::ObjectType objectType = PhysicsObjectCondition::Fluid;
	if(  type == "Fluid") {
		objectType = PhysicsObjectCondition::Fluid;
	}
	else if( type == "Obstacle" ) {
		objectType = PhysicsObjectCondition::Rigid;
	}
	else if( type == "Rigid") {
		objectType = PhysicsObjectCondition::RigidTwoWay;
	}
	else{
		Debug::Assert( false );
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

