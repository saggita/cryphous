#include "ApplicationSettings.h"

#include "../CrystalGeom/Vector3d.h"
#include "../CrystalGeom/Box.h"
#include "../CrystalPhysics/PhysicsObjectCondition.h"
#include "../CrystalGraphics/GraphicsSettings.h"
#include "../CrystalPhysics/PhysicsObjectFactory.h"
#include "../CrystalPhysics/SimulationSetting.h"
#include "../CrystalPhysics/Simulation.h"
#include "../CrystalGraphics/Renderer.h"

#include <boost/foreach.hpp>

using namespace Crystal::Geom;
using namespace Crystal::Physics;
using namespace Crystal::Graphics;
using namespace Crystal::Command;

using namespace System::Xml;

ApplicationSettings::ApplicationSettings(void)
{
	factory = new PhysicsObjectFactory;
	simulation = new Simulation;
	simulationSetting = new SimulationSetting;
	renderer = new Renderer;
	conditions = new std::list<PhysicsObjectCondition>;
}

ApplicationSettings::~ApplicationSettings()
{
	delete conditions;
	delete renderer;
	delete simulationSetting;
	delete simulation;
	delete factory;
}

void ApplicationSettings::refresh()
{
	factory->init();
	BOOST_FOREACH(const PhysicsObjectCondition& condition, *conditions ) {
		factory->createPhysicsObject(condition, *simulationSetting);
	}
	renderer->init();	
	simulation->init();
}

double ApplicationSettings::getParticleDiameter()
{
	return simulationSetting->particleDiameter;
}

void ApplicationSettings::setParticleDiameter(const double diameter)
{
	simulationSetting->particleDiameter = diameter;
}