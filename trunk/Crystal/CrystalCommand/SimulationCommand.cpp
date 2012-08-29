#include "SimulationCommand.h"

#include "../CrystalPhysics/PhysicsObject.h"
#include "../CrystalPhysics/PhysicsObjectFactory.h"
#include "../CrystalPhysics/Simulation.h"
#include "../CrystalPhysics/Profiler.h"
#include "../CrystalPhysics/SimulationSetting.h"
#include "ApplicationSettings.h"

#include "../CrystalGraphics/Renderer.h"

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

List<ManagedPosition^>^ SimulationCommand::getManagedPositions()
{
	PhysicsObjectFactory* factory = ApplicationSettings::get()->factory;
	const ParticleVector& nativeParticles = factory->getOrderedParticles();
	return ParticleMarshaler::convertToManagedPositions( nativeParticles );
}

List<ManagedVector^>^ SimulationCommand::getManagedNormals()
{
	PhysicsObjectFactory* factory = ApplicationSettings::get()->factory;
	const ParticleVector& nativeParticles = factory->getOrderedParticles();
	return ParticleMarshaler::convertToManagedNormals( nativeParticles );
}
