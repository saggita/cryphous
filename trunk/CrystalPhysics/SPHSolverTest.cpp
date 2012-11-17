#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include "../CrystalPhysics/SPHSolver.h"
#include "../CrystalPhysics/PhysicsObject.h"
#include "../CrystalPhysics/SimulationSetting.h"

#include "../CrystalPhysics/PhysicsObjectFactory.h"
#include "../CrystalGeom/Box.h"
#include "../CrystalGeom/Vector3d.h"
#include "../CrystalGeom/Vector3d.h"

#include "../CrystalPhysics/Particle.h"
#include "../CrystalPhysics/ParticleFactory.h"

#include "../CrystalPhysics/SearchParticleFactory.h"

using namespace Crystal::Geom;
using namespace Crystal::Physics;

BOOST_AUTO_TEST_CASE(SPH_SOLVER_TEST)
{
	PhysicsObjectFactory factory;
	SimulationSetting setting;
	setting.particleDiameter = 1.0;
	std::vector<Vector3d> points;
	points.push_back( Vector3d(0.0, 0.0, 0.0 ) );
	points.push_back( Vector3d(1.0, 0.0, 0.0 ) );
	PhysicsObjectCondition condition( points, 1000.0f, 1.0f, 0.4f, PhysicsObjectCondition::Fluid );
	PhysicsObject* fluid = factory.createPhysicsObject( condition, setting );
	PhysicsObjectVector objects( 1, fluid);
	SearchParticleFactory spFactory( factory.getParticles(), setting.getEffectLength() );
	SPHSolver solver( &factory, setting, spFactory.getSearchParticles());
	solver.calculateInteraction();
	
	BOOST_CHECK( fluid->getParticles().front()->force != Vector3d( 0.0, 0.0, 0.0 ) );
	//BOOST_CHECK( fluid->getParticles().front()->force == ( -1.0 * fluid->getParticles().back()->force ) );
	BOOST_CHECK( fluid->getParticles().front()->normal != Vector3d( 0.0, 0.0, 0.0 ) );
	BOOST_CHECK( fluid->getParticles().front()->normal == (-1.0 * fluid->getParticles().back()->normal) );
}