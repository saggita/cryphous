#include "Point3dTest.h"

#include <boost/test/unit_test.hpp>

#include "../CrystalGeom/Point3d.h"
#include "../CrystalGeom/Tolerances.h"
#include "../CrystalGeom/Matrix3d.h"

using namespace Crystal::Geom;

Point3dTest::Point3dTest(void)
{
	{
		Point3d pointX( 10.0, 10.0, 10.0 );
		Point3d pointY( 10.0, 10.0, 10.0 );
		BOOST_CHECK( pointX == pointY );
	}

	{
		Point3d pointX( 10.0, 10.0, 10.0 );
		Point3d pointY( 10.0, 10.0, 0.0 );
		BOOST_CHECK( pointX != pointY );
	}

	{
		Point3d pointX( 10.0, 10.0, 10.0 );
		Point3d pointY( 10.0, 10.0, 0.0 );
		const double result = pointX.getDistanceSquared( pointY );
		const double expected = 100.0;
		BOOST_CHECK( result == expected );
	}

	{
		Point3d pointX( 10.0, 10.0, 10.0 );
		Point3d pointY( 10.0, 10.0, 0.0 );
		const double result = pointX.getDistance( pointY );
		const double expected = 10.0;
		BOOST_CHECK( Tolerances::isEqualAsDistance( result, expected ) );
	}

	{
		Point3d point( 10.0, 10.0, 10.0 );
		Matrix3d matrix;
		matrix.setRotateX( Tolerances::getPI() );
		const Point3d& result = point.getRotated( matrix );
		const Point3d expected( 10.0, -10.0, -10.0 );
		BOOST_CHECK( result == expected );
	}

	{
		Point3d point( 10.0, 10.0, 10.0 );
		Matrix3d matrix;
		matrix.setRotateY( Tolerances::getPI() );
		const Point3d& result = point.getRotated( matrix );
		const Point3d expected( -10.0, 10.0, -10.0);
		BOOST_CHECK( result == expected );
	}

	{
		Point3d point( 10.0, 10.0, 10.0 );
		Matrix3d matrix;
		matrix.setRotateZ( Tolerances::getPI() );
		const Point3d& result = point.getRotated( matrix);
		const Point3d expected( -10.0, -10.0, 10.0 );
		BOOST_CHECK( result == expected );
	}

	{
		Point3d point( 10.0, 10.0, 10.0 );
		const Point3d& moved = point + Vector3d( 1.0, 4.0, 0.0 );
		BOOST_CHECK( moved == Point3d( 11.0, 14.0, 10.0 ) );
	}

	{
		Point3d point( 10.0, 10.0, 10.0 );
		point.addPertubation( 0.5, 1.0, 2.0 );
		BOOST_CHECK( point != Point3d( 10.0, 10.0, 10.0 ) );
	}

	{
		Point3d point( 10.0, 10.0, 10.0 );
		const Point3d& pertubated = point.getPertubated( 0.5, 1.0, 2.0 );
		BOOST_CHECK( point == Point3d( 10.0, 10.0, 10.0 ) );
		BOOST_CHECK( pertubated != point );
	}
}
