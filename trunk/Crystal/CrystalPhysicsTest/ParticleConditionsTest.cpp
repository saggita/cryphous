#include "ParticleConditionsTest.h"

#include "../CrystalPhysics/ParticleConditions.h"

#include "../CrystalGeom/Box.h"
#include "../CrystalGeom/Point3d.h"

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
	ParticleConditions conditions( Box(Point3d( 0.0, 0.0, 0.0), Point3d( 1.0, 1.0, 1.0)), 0.5, 1.0 );
	const std::list<Point3d>& points = conditions.getInnerPoints();
	BOOST_CHECK_EQUAL( points.size(), 8 );
	BOOST_CHECK_EQUAL( conditions.getXNumber(), 2 );
	BOOST_CHECK_EQUAL( conditions.getYNumber(), 2 );
	BOOST_CHECK_EQUAL( conditions.getZNumber(), 2 );
}

void ParticleConditionsTest::getInnerPointsEmptyTest()
{
	ParticleConditions conditions( Box(Point3d( 0.0, 0.0, 0.0), Point3d( 0.0, 0.0, 0.0)), 0.5, 1.0 );
	const std::list<Point3d>& points = conditions.getInnerPoints();
	BOOST_CHECK( points.empty() );
	BOOST_CHECK_EQUAL( conditions.getXNumber(), 0 );
	BOOST_CHECK_EQUAL( conditions.getYNumber(), 0 );
	BOOST_CHECK_EQUAL( conditions.getZNumber(), 0 );
}
