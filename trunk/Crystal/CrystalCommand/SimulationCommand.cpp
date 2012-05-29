#include "SimulationCommand.h"

#include "../CrystalPhysics/PhysicsObjectFactory.h"
#include "../CrystalPhysics/Simulation.h"
#include "../CrystalPhysics/Profiler.h"
#include "../CrystalPhysics/SimulationSetting.h"

#include "../CrystalGraphics/Renderer.h"

using namespace Crystal::Physics;
using namespace Crystal::Graphics;
using namespace Crystal::Command;

SimulationCommand::SimulationCommand(void)
{
}

void SimulationCommand::refresh()
{
	PhysicsObjectFactory::get()->reCreatePhysicsObject( SimulationSetting::get()->effectLength);
	Renderer::get()->init();	
	Simulation::get()->init();
	Profiler::get()->init();
	stopWatch->Reset();
}

void SimulationCommand::proceed()
{
	stopWatch->Start();
	Simulation::get()->simulate();
	stopWatch->Stop();
}

int SimulationCommand::getStep()
{
	return Simulation::get()->getStep();
}