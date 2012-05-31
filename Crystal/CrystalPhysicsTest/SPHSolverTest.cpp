
#include "SPHSolverTest.h"

#include "../CrystalPhysics/SPHSolver.h"
#include "../CrystalPhysics/PhysicsObject.h"
#include "../CrystalPhysics/SimulationSetting.h"

#include "../CrystalPhysics/PhysicsObjectFactory.h"
#include "../CrystalPhysics/PhysicsObjectCondition.h"
#include "../CrystalGeom/Box.h"
#include "../CrystalGeom/Point3d.h"
#include "../CrystalGeom/Vector3d.h"

#include "../CrystalPhysics/Particle.h"
#include "../CrystalPhysics/ParticleDerive.h"
#include "../CrystalPhysics/ParticleFactory.h"

#include <boost/test/unit_test.hpp>

using namespace Crystal::Geom;
using namespace Crystal::Physics;

SPHSolverTest::SPHSolverTest(void)
{
	PhysicsObjectFactory factory;
	SimulationSetting setting;
	setting.effectLength = 1.3;
	Box boundaryBox( Point3d( 0.0, 0.0, 0.0), Point3d( 10.0, 1.0, 1.0) );
	PhysicsObjectCondition condition( boundaryBox, 1000.0, 1.0, 8.0, 0.4, PhysicsObjectCondition::Fluid );
	PhysicsObject* fluid = factory.createPhysicsObject( condition, 1.0 );
	PhysicsObjectList objects( 1, fluid);
	SPHSolver solver( &factory, setting);
	solver.calculateInteraction();
	
	BOOST_CHECK( fluid->getParticles().front()->getDerive()->force != Vector3d( 0.0, 0.0, 0.0 ) );
}