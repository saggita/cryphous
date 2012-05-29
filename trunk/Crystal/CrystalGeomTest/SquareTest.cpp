#include "SquareTest.h"

#include "../CrystalGeom/Square.h"

#include <boost/test/unit_test.hpp>

using namespace Crystal::Geom;

SquareTest::SquareTest(void)
{
	{
		Square square( Point3d( 0.0, 0.0, 0.0 ), 2.0 );
		BOOST_CHECK_EQUAL( square.getArea(), 4.0 );
		const std::vector<Point3d>& points = square.getPoints();
		BOOST_CHECK( points[0] == Point3d( -1.0, 1.0, 0.0 ) );
		BOOST_CHECK( points[1] == Point3d( -1.0, -1.0, 0.0 ) );
		BOOST_CHECK( points[2] == Point3d( 1.0, -1.0, 0.0 ) );
		BOOST_CHECK( points[3] == Point3d( 1.0, 1.0, 0.0 ) );
	}
}

SquareTest::~SquareTest(void)
{
}
