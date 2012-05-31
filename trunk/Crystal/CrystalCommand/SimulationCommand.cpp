#include "SimulationCommand.h"

#include "../CrystalPhysics/PhysicsObjectFactory.h"
#include "../CrystalPhysics/Simulation.h"
#include "../CrystalPhysics/Profiler.h"
#include "../CrystalPhysics/SimulationSetting.h"
#include "ApplicationSettings.h"

#include "../CrystalGraphics/Renderer.h"

using namespace Crystal::Physics;
using namespace Crystal::Graphics;
using namespace Crystal::Command;

SimulationCommand::SimulationCommand(void)
{
}

void SimulationCommand::refresh()
{
	ApplicationSettings::get()->factory->reCreatePhysicsObject( ApplicationSettings::get()->simulationSetting->effectLength);
	Renderer::get()->init();	
	Simulation::get()->init();
	Profiler::get()->init();
	stopWatch->Reset();
}

void SimulationCommand::proceed()
{
	stopWatch->Start();
	Simulation::get()->simulate( ApplicationSettings::get()->factory, *(ApplicationSettings::get()->simulationSetting) );
	stopWatch->Stop();
}

int SimulationCommand::getStep()
{
	return Simulation::get()->getStep();
}