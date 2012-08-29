#include "ApplicationSettings.h"

#include "../CrystalGeom/Vector3d.h"
#include "../CrystalGeom/Box.h"
#include "../CrystalGraphics/GraphicsSettings.h"
#include "../CrystalPhysics/PhysicsObjectFactory.h"
#include "../CrystalPhysics/SimulationSetting.h"
#include "../CrystalPhysics/Simulation.h"
#include "../CrystalGraphics/Renderer.h"

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
	graphicsSettings = new GraphicsSettings;
	renderer = new Renderer(*graphicsSettings);
	conditions = new std::list<PhysicsObjectCondition>;
}

ApplicationSettings::~ApplicationSettings()
{
	delete graphicsSettings;
	delete conditions;
	delete renderer;
	delete simulationSetting;
	delete simulation;
	delete factory;
}

void ApplicationSettings::refresh()
{
	factory->init();
	for( std::list<PhysicsObjectCondition>::iterator iter = conditions->begin(); iter != conditions->end(); ++iter ) {
		factory->createPhysicsObject((*iter), *simulationSetting);
	}
	renderer->init();	
	simulation->init();
}

float ApplicationSettings::getParticleDiameter()
{
	return simulationSetting->particleDiameter;
}

void ApplicationSettings::setParticleDiameter(const float diameter)
{
	simulationSetting->particleDiameter = diameter;
}