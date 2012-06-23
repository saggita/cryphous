#include "ParticleConditionsTest.h"

#include "../CrystalPhysics/ParticleConditions.h"

#include "../CrystalGeom/Box.h"
#include "../CrystalGeom/Vector3d.h"

#include <boost/test/unit_test.hpp>

using namespace Crystal::Geom;
using namespace Crystal::Physics;

ParticleConditionsTest::ParticleConditionsTest(void)
{
	getInnerPointsTest();
	getInnerPointsEmptyTest();
}

void ParticleConditionsTest::getInnerPointsTest()
{
	ParticleConditions conditions( Box(Vector3d( 0.0, 0.0, 0.0), Vector3d( 1.0, 1.0, 1.0)), 0.5, 1.0 );
	const std::vector<Vector3d>& points = conditions.getInnerPoints();
	BOOST_CHECK_EQUAL( points.size(), 8 );
}

void ParticleConditionsTest::getInnerPointsEmptyTest()
{
	ParticleConditions conditions( Box(Vector3d( 0.0, 0.0, 0.0), Vector3d( 0.0, 0.0, 0.0)), 0.5, 1.0 );
	const std::vector<Vector3d>& points = conditions.getInnerPoints();
	BOOST_CHECK( points.empty() );
}

void ParticleConditionsTest::getArbitaryPointsTest()
{
	std::vector<Vector3d> points;
	points.push_back( Vector3d(0.0, 0.0, 0.0) );
	points.push_back( Vector3d(1.0, 1.0, 1.0) );
	ParticleConditions conditions( points, 0.5, 1.0 );
	BOOST_CHECK_EQUAL( conditions.getInnerPoints().size(), 2 );
}