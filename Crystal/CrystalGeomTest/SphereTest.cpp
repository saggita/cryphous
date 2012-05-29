#include "SphereTest.h"

#include "../CrystalGeom/Sphere.h"
#include "../CrystalGeom/Tolerances.h"

#include <boost/test/unit_test.hpp>

using namespace Crystal::Geom;

void testGetVolume()
{
	Sphere sphere( Point3d( 0.0, 0.0, 0.0), 1.0 );
	const double result = sphere.getVolume();
	const double expected = 4.0 / 3.0 * Tolerances::getPI();
	BOOST_CHECK_EQUAL( result, expected );
}

void testIsDegenerated()
{
	Sphere sphere( Point3d( 0.0, 0.0, 0.0), 0.0 );
	BOOST_CHECK( sphere.isDegenerated() );
}

void testIsInterior()
{
	Sphere sphere( Point3d( 0.0, 0.0, 0.0 ), 1.0 );
	BOOST_CHECK( sphere.isInterior( Point3d( 0.0, 0.0, 0.5 ) ) );
}

void testIsExterior()
{
	Sphere sphere( Point3d( 0.0, 0.0, 0.0 ), 1.0 );
	BOOST_CHECK( sphere.isExterior( Point3d( 0.0, 2.0, 0.0 ) ) );
}

SphereTest::SphereTest(void)
{
	testGetVolume();
	testIsDegenerated();
	testIsInterior();
	testIsExterior();
}

SphereTest::~SphereTest(void)
{
}