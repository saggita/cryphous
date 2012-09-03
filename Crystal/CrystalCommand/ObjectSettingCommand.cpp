#include "ObjectSettingCommand.h"

#include "../CrystalPhysics/PhysicsObjectFactory.h"
#include "../CrystalGeom/Vector3d.h"
#include "../CrystalGeom/Box.h"
#include "../CrystalPhysics/SimulationSetting.h"

#include "ApplicationSettings.h"
#include "ParticleMarshaler.h"

using namespace Crystal::Geom;
using namespace Crystal::Physics;
using namespace Crystal::Command;

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Diagnostics;
using namespace System::IO;

ObjectSettingCommand::ObjectSettingCommand()
{
}

ObjectSettingCommand::~ObjectSettingCommand()
{
}

void ObjectSettingCommand::refresh()
{
	ApplicationSettings::get()->conditions->clear();
	ApplicationSettings::get()->factory->init();
}

void ObjectSettingCommand::createPhysicsObject(String^ type, const float density, const float pressureCoe, const float viscosityCoe, System::Collections::Generic::List<ManagedPosition^>^ managedPositions)
{
	std::vector<Geom::Vector3d> points = ParticleMarshaler::convertToNative(managedPositions);

	const Box& box = ApplicationSettings::get()->simulationSetting->boundaryBox;

	PhysicsObjectCondition::ObjectType objectType = PhysicsObjectCondition::Fluid;
	if(  type == "Fluid") {
		objectType = PhysicsObjectCondition::Fluid;
	}
	else if( type == "Obstacle" ) {
		objectType = PhysicsObjectCondition::Obstacle;
	}
	else if( type == "Rigid") {
		objectType = PhysicsObjectCondition::Rigid;
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

void ObjectSettingCommand::addParticles(int index, System::Collections::Generic::List<ManagedPosition^> ^managedPosition, System::Collections::Generic::List<ManagedPosition^> ^managedVelocity)
{
	std::vector<Geom::Vector3d> points = ParticleMarshaler::convertToNative(managedPosition);
	std::vector<Geom::Vector3d> velocities = ParticleMarshaler::convertToNative(managedVelocity);

	ApplicationSettings::get()->factory->addParticles(index, points, velocities );
}