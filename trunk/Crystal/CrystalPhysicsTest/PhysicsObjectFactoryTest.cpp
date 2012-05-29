
#include "PhysicsObjectFactoryTest.h"

#include "../CrystalPhysics/PhysicsObjectFactory.h"
#include "../CrystalPhysics/PhysicsObjectCondition.h"
#include "../CrystalPhysics/Fluid.h"
#include "../CrystalGeom/Box.h"
#include "../CrystalGeom/Point3d.h"

#include <boost/test/unit_test.hpp>

using namespace Crystal::Geom;
using namespace Crystal::Physics;

PhysicsObjectFactoryTest::PhysicsObjectFactoryTest(void)
{
	PhysicsObjectFactory::get()->init();
	createFluidTest();
	createRigidTest();
	createRigidTwoWayTest();
}

void PhysicsObjectFactoryTest::createFluidTest()
{
	PhysicsObjectCondition condition( Box(), 1000.0, 1.0, 5.0, 0.4, PhysicsObjectCondition::Fluid );
	PhysicsObject* fluid = PhysicsObjectFactory::get()->createPhysicsObject( condition, 1.0);
	BOOST_CHECK( fluid != 0 );
	BOOST_CHECK_EQUAL( fluid->getID(), 0 );
	BOOST_CHECK_EQUAL( fluid->getType(), PhysicsObject::Fluid );
	BOOST_CHECK( !fluid->getParticles().empty() );
	BOOST_CHECK( fluid->getParticleGrid().empty() );
	PhysicsObjectFactory::get()->init();
}

void PhysicsObjectFactoryTest::createRigidTest()
{
	PhysicsObjectCondition condition( Box(), 1000.0, 1.0, 5.0, 0.4, PhysicsObjectCondition::Rigid);
	PhysicsObject* rigid = PhysicsObjectFactory::get()->createPhysicsObject( condition, 1.0);
	BOOST_CHECK( rigid != 0 );
	BOOST_CHECK_EQUAL( rigid->getID(), 0 );
	BOOST_CHECK_EQUAL( rigid->getType(), PhysicsObject::Rigid );
	BOOST_CHECK( !rigid->getParticles().empty() );
	BOOST_CHECK( !rigid->getParticleGrid().empty() );
	PhysicsObjectFactory::get()->init();
}

void PhysicsObjectFactoryTest::createRigidTwoWayTest()
{
	PhysicsObjectCondition condition( Box(), 1000.0, 1.0, 5.0, 0.4, PhysicsObjectCondition::RigidTwoWay );
	PhysicsObject* rigid = PhysicsObjectFactory::get()->createPhysicsObject( condition, 1.0);
	BOOST_CHECK( rigid != 0 );
	BOOST_CHECK_EQUAL( rigid->getID(), 0 );
	BOOST_CHECK_EQUAL( rigid->getType(), PhysicsObject::Rigid );
	BOOST_CHECK( !rigid->getParticles().empty() );
	BOOST_CHECK( !rigid->getParticleGrid().empty() );
	PhysicsObjectFactory::get()->init();
}