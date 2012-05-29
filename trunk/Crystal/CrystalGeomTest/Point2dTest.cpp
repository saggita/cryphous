#include "Point2dTest.h"

#include <boost/test/unit_test.hpp>

#include "../CrystalGeom/Point2d.h"
#include "../CrystalGeom/Tolerances.h"
#include "../CrystalGeom/Matrix2d.h"

using namespace Crystal::Geom;

Point2dTest::Point2dTest(void)
{
	{
		Point2d pointX( 10.0, 10.0 );
		Point2d pointY( 10.0, 10.0 );
		BOOST_CHECK( pointX == pointY );
	}

	{
		Point2d pointX( 10.0, 10.0 );
		Point2d pointY( 10.0, 0.0 );
		BOOST_CHECK( pointX != pointY );
	}

	{
		Point2d pointX( 10.0, 10.0 );
		Point2d pointY( 10.0, 0.0 );
		const double result = pointX.getDistanceSquared( pointY );
		const double expected = 100.0;
		BOOST_CHECK( result == expected );
	}

	{
		Point2d pointX( 10.0, 10.0 );
		Point2d pointY( 10.0, 0.0 );
		const double result = pointX.getDistance( pointY );
		const double expected = 10.0;
		BOOST_CHECK( Tolerances::isEqualAsDistance( result, expected ) );
	}

	{
		Point2d point( 10.0, 10.0 );
		Matrix2d matrix;
		matrix.setRotate( Tolerances::getPI() );
		const Point2d& result = point.getRotated( matrix);
		const Point2d expected( -10.0, -10.0 );
		BOOST_CHECK( result == expected );
	}

	{
		Point2d point( 10.0, 10.0 );
		const Point2d& moved = point + Vector2d( 1.0, 4.0 );
		BOOST_CHECK( moved == Point2d( 11.0, 14.0 ) );
	}

	{
		Point2d point( 10.0, 10.0 );
		point.addPertubation( 0.5, 1.0 );
		BOOST_CHECK( point != Point2d( 10.0, 10.0 ) );
	}

	{
		Point2d point( 10.0, 10.0 );
		const Point2d& pertubated = point.getPertubated( 0.5, 1.0 );
		BOOST_CHECK( point == Point2d( 10.0, 10.0 ) );
		BOOST_CHECK( pertubated != point );
	}
}

Point2dTest::~Point2dTest()
{
}