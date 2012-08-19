#include "SimulationCommand.h"

#include "../CrystalPhysics/PhysicsObject.h"
#include "../CrystalPhysics/PhysicsObjectFactory.h"
#include "../CrystalPhysics/Simulation.h"
#include "../CrystalPhysics/Profiler.h"
#include "../CrystalPhysics/SimulationSetting.h"
#include "ApplicationSettings.h"

#include "../CrystalGraphics/Renderer.h"

#include <boost/foreach.hpp>

using namespace Crystal::Physics;
using namespace Crystal::Graphics;
using namespace Crystal::Command;

using namespace System::Collections::Generic;

SimulationCommand::SimulationCommand(void)
{
}

void SimulationCommand::refresh()
{
	ApplicationSettings::get()->refresh();
	Profiler::get()->init();
}

void SimulationCommand::proceed()
{
	ApplicationSettings::get()->simulation->simulate( ApplicationSettings::get()->factory, *(ApplicationSettings::get()->simulationSetting) );
}

int SimulationCommand::getStep()
{
	return ApplicationSettings::get()->simulation->getStep();
}

List<List<ManagedPosition^>^>^ SimulationCommand::getManagedPositions()
{
	List<List<ManagedPosition^>^>^ results = gcnew List<List<ManagedPosition^>^>();
	PhysicsObjectFactory* factory = ApplicationSettings::get()->factory;
	BOOST_FOREACH( PhysicsObject* object, factory->getPhysicsObjects() ) {
		const ParticleVector& nativeParticles = object->getParticles();
		results->Add( ParticleMarshaler::convertToManagedPositions( nativeParticles) );
	}
	return results;
}

List<List<ManagedVector^>^>^ SimulationCommand::getManagedNormals()
{
	List<List<ManagedVector^>^>^ results = gcnew List<List<ManagedVector^>^>();
	PhysicsObjectFactory* factory = ApplicationSettings::get()->factory;
	BOOST_FOREACH( PhysicsObject* object, factory->getPhysicsObjects() ) {
		const ParticleVector& nativeParticles = object->getParticles();
		results->Add( ParticleMarshaler::convertToManagedNormals( nativeParticles) );
	}
	return results;
}
