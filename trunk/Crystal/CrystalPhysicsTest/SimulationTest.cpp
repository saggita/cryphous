
#include "SimulationTest.h"

#include "../CrystalPhysics/Simulation.h"

#include "../CrystalGeom/Box.h"

#include "../CrystalPhysics/PhysicsObject.h"
#include "../CrystalPhysics/PhysicsObjectFactory.h"
#include "../CrystalPhysics/PhysicsObjectCondition.h"

#include "../CrystalPhysics/ParticleFactory.h"
#include "../CrystalPhysics/Particle.h"

using namespace Crystal::Geom;
using namespace Crystal::Physics;

SimulationTest::SimulationTest(void)
{
	PhysicsObjectCondition condition( Box(), 1000.0, 1.0, 5.0, 0.4, PhysicsObjectCondition::Fluid );
	PhysicsObjectFactory factory;
	factory.createPhysicsObject( condition, 1.0 );
	SimulationSetting setting;
	setting.particleDiameter = 1.0;
	Simulation simulation;
	simulation.simulate( &factory, setting);
}
