
#include "PhysicsObjectFactoryTest.h"

#include "../CrystalPhysics/PhysicsObjectFactory.h"
#include "../CrystalPhysics/PhysicsObjectCondition.h"
#include "../CrystalPhysics/Fluid.h"
#include "../CrystalGeom/Box.h"
#include "../CrystalGeom/Vector3d.h"

#include <boost/test/unit_test.hpp>

using namespace Crystal::Geom;
using namespace Crystal::Physics;

PhysicsObjectFactoryTest::PhysicsObjectFactoryTest(void)
{
	createFluidTest();
	createRigidTest();
	createRigidTwoWayTest();
}

void PhysicsObjectFactoryTest::createFluidTest()
{
	PhysicsObjectFactory factory;
	SimulationSetting setting;
	setting.particleDiameter = 1.0;
	PhysicsObjectCondition condition( Box(), 1000.0, 1.0, 0.4, PhysicsObjectCondition::Fluid );
	PhysicsObject* fluid = factory.createPhysicsObject( condition, setting);
	BOOST_CHECK( fluid != 0 );
	BOOST_CHECK_EQUAL( fluid->getID(), 0 );
	BOOST_CHECK_EQUAL( fluid->getType(), PhysicsObject::Fluid );
	BOOST_CHECK( !fluid->getParticles().empty() );
	BOOST_CHECK_EQUAL( factory.getOrderedParticles().size(), factory.getSortedParticles().size() );
}

void PhysicsObjectFactoryTest::createRigidTest()
{
	PhysicsObjectFactory factory;
	SimulationSetting setting;
	setting.particleDiameter = 1.0;
	PhysicsObjectCondition condition( Box(), 1000.0, 1.0, 0.4, PhysicsObjectCondition::Rigid);
	PhysicsObject* rigid = factory.createPhysicsObject( condition, setting);
	BOOST_CHECK( rigid != 0 );
	BOOST_CHECK_EQUAL( rigid->getID(), 0 );
	BOOST_CHECK_EQUAL( rigid->getType(), PhysicsObject::Rigid );
	BOOST_CHECK( !rigid->getParticles().empty() );
	BOOST_CHECK_EQUAL( factory.getOrderedParticles().size(), factory.getSortedParticles().size() );
}

void PhysicsObjectFactoryTest::createRigidTwoWayTest()
{
	PhysicsObjectFactory factory;
	SimulationSetting setting;
	setting.particleDiameter = 1.0;
	PhysicsObjectCondition condition( Box(), 1000.0, 1.0, 0.4, PhysicsObjectCondition::RigidTwoWay );
	PhysicsObject* rigid = factory.createPhysicsObject( condition, setting);
	BOOST_CHECK( rigid != 0 );
	BOOST_CHECK_EQUAL( rigid->getID(), 0 );
	BOOST_CHECK_EQUAL( rigid->getType(), PhysicsObject::Rigid );
	BOOST_CHECK( !rigid->getParticles().empty() );
	BOOST_CHECK_EQUAL( factory.getOrderedParticles().size(), factory.getSortedParticles().size() );
}