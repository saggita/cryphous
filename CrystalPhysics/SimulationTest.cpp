#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include "../CrystalPhysics/Simulation.h"

#include "../CrystalGeom/Vector3d.h"

#include "../CrystalPhysics/PhysicsObject.h"
#include "../CrystalPhysics/PhysicsObjectFactory.h"

#include "../CrystalPhysics/ParticleFactory.h"
#include "../CrystalPhysics/Particle.h"

#include "../CrystalPhysics/LightSource.h"

using namespace Crystal::Geom;
using namespace Crystal::Physics;

BOOST_AUTO_TEST_CASE(SIMULATION_TEST)
{
	SimulationSetting setting;
	setting.particleDiameter = 1.0;
	std::vector<Vector3d> point;
	point.push_back( Vector3d(0.0, 0.0, 0.0 ) );
	PhysicsObjectCondition condition( point, 1000.0f, 1.0f, 0.4f, PhysicsObjectCondition::Fluid );
	PhysicsObjectFactory factory;
	factory.createPhysicsObject( condition, setting );

	LightSource lightSource;

	Simulation simulation;
	simulation.simulate( &factory, &lightSource, setting);
}
