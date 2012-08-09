#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include "../CrystalPhysics/PhysicsObjectFactory.h"
#include "../CrystalPhysics/Fluid.h"
#include "../CrystalGeom/Box.h"
#include "../CrystalGeom/Vector3d.h"

using namespace Crystal::Geom;
using namespace Crystal::Physics;

BOOST_AUTO_TEST_CASE(PHYSICS_OBJECT_FACTORY_TEST)
{
	{
		PhysicsObjectFactory factory;
		SimulationSetting setting;
		setting.particleDiameter = 1.0;
		std::vector<Vector3d> points;
		points.push_back( Vector3d(0.0, 0.0, 0.0 ) );
		PhysicsObjectCondition condition( points, 1000.0f, 1.0f, 0.4f, PhysicsObjectCondition::Fluid );
		PhysicsObject* fluid = factory.createPhysicsObject( condition, setting);
		BOOST_CHECK( fluid != 0 );
		BOOST_CHECK_EQUAL( fluid->getID(), 0 );
		BOOST_CHECK_EQUAL( fluid->getType(), PhysicsObject::Fluid );
		BOOST_CHECK( !fluid->getParticles().empty() );
		BOOST_CHECK_EQUAL( factory.getOrderedParticles().size(), factory.getSortedParticles().size() );
	}

	{
		PhysicsObjectFactory factory;
		SimulationSetting setting;
		setting.particleDiameter = 1.0;
		std::vector<Vector3d> points;
		points.push_back( Vector3d(0.0, 0.0, 0.0 ) );
		PhysicsObjectCondition condition( points, 1000.0f, 1.0f, 0.4f, PhysicsObjectCondition::Obstacle);
		PhysicsObject* rigid = factory.createPhysicsObject( condition, setting);
		BOOST_CHECK( rigid != 0 );
		BOOST_CHECK_EQUAL( rigid->getID(), 0 );
		BOOST_CHECK_EQUAL( rigid->getType(), PhysicsObject::Obstacle );
		BOOST_CHECK( !rigid->getParticles().empty() );
		BOOST_CHECK_EQUAL( factory.getOrderedParticles().size(), factory.getSortedParticles().size() );
	}

	{
		PhysicsObjectFactory factory;
		SimulationSetting setting;
		setting.particleDiameter = 1.0;
		std::vector<Vector3d> points;
		points.push_back( Vector3d(0.0, 0.0, 0.0 ) );
		PhysicsObjectCondition condition( points, 1000.0f, 1.0f, 0.4f, PhysicsObjectCondition::Rigid );
		PhysicsObject* rigid = factory.createPhysicsObject( condition, setting);
		BOOST_CHECK( rigid != 0 );
		BOOST_CHECK_EQUAL( rigid->getID(), 0 );
		BOOST_CHECK_EQUAL( rigid->getType(), PhysicsObject::Rigid );
		BOOST_CHECK( !rigid->getParticles().empty() );
		BOOST_CHECK_EQUAL( factory.getOrderedParticles().size(), factory.getSortedParticles().size() );
	}
}