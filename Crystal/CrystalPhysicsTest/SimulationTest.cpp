
#include "SimulationTest.h"

#include "../CrystalPhysics/Simulation.h"

#include "../CrystalGeom/Vector3d.h"

#include "../CrystalPhysics/PhysicsObject.h"
#include "../CrystalPhysics/PhysicsObjectFactory.h"

#include "../CrystalPhysics/ParticleFactory.h"
#include "../CrystalPhysics/Particle.h"

using namespace Crystal::Geom;
using namespace Crystal::Physics;

SimulationTest::SimulationTest(void)
{
	SimulationSetting setting;
	setting.particleDiameter = 1.0;
	std::vector<Vector3d> point;
	point.push_back( Vector3d(0.0, 0.0, 0.0 ) );
	PhysicsObjectCondition condition( point, 1000.0, 1.0, 0.4, PhysicsObjectCondition::Fluid );
	PhysicsObjectFactory factory;
	factory.createPhysicsObject( condition, setting );

	Simulation simulation;
	simulation.simulate( &factory, setting);
}
