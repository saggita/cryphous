
#include "SPHSolverTest.h"

#include "../CrystalPhysics/SPHSolver.h"
#include "../CrystalPhysics/PhysicsObject.h"
#include "../CrystalPhysics/SimulationSetting.h"

#include "../CrystalPhysics/PhysicsObjectFactory.h"
#include "../CrystalGeom/Box.h"
#include "../CrystalGeom/Vector3d.h"
#include "../CrystalGeom/Vector3d.h"

#include "../CrystalPhysics/Particle.h"
#include "../CrystalPhysics/ParticleFactory.h"

#include <boost/test/unit_test.hpp>

using namespace Crystal::Geom;
using namespace Crystal::Physics;

SPHSolverTest::SPHSolverTest(void)
{
	PhysicsObjectFactory factory;
	SimulationSetting setting;
	setting.particleDiameter = 1.0;
	std::vector<Vector3d> points;
	points.push_back( Vector3d(0.0, 0.0, 0.0 ) );
	PhysicsObjectCondition condition( points, 1000.0, 1.0, 0.4, PhysicsObjectCondition::Fluid );
	PhysicsObject* fluid = factory.createPhysicsObject( condition, setting );
	PhysicsObjectList objects( 1, fluid);
	SPHSolver solver( &factory, setting);
	solver.calculateInteraction();
	
	BOOST_CHECK( fluid->getParticles().front()->force != Vector3d( 0.0, 0.0, 0.0 ) );
}