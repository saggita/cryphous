#include "Point4dTest.h"

#include <boost/test/unit_test.hpp>

#include "../CrystalGeom/Point4d.h"
#include "../CrystalGeom/Tolerances.h"
#include "../CrystalGeom/Matrix4d.h"

using namespace Crystal::Geom;

Point4dTest::Point4dTest(void)
{
	{
		const Point4d pointX( 10.0, 10.0, 10.0, 10.0 );
		const Point4d pointY( 10.0, 10.0, 10.0, 10.0 );
		BOOST_CHECK( pointX == pointY );
	}

	{
		const Point4d pointX( 10.0, 10.0, 10.0, 10.0 );
		const Point4d pointY( 10.0, 10.0, 10.0, 0.0 );
		BOOST_CHECK( pointX != pointY );
	}

	{
		const Point4d pointX( 10.0, 10.0, 10.0, 10.0 );
		const Point4d pointY( 10.0, 10.0, 10.0, 0.0 );
		const double result = pointX.getDistanceSquared( pointY );
		const double expected = 100.0;
		BOOST_CHECK( result == expected );
	}

	{
		const Point4d pointX( 10.0, 10.0, 10.0, 10.0 );
		const Point4d pointY( 10.0, 10.0, 10.0, 0.0 );
		const double result = pointX.getDistance( pointY );
		const double expected = 10.0;
		BOOST_CHECK( Tolerances::isEqualAsDistance( result, expected ) );
	}

	/*{
		Point4d point( 10.0, 10.0, 10.0, 10.0 );
		Matrix4d matrix;
		matrix.setRotateX( Tolerances::getPI() );
		const Point4d& result = point.getRotated( matrix );
		const Point4d expected( 10.0, -10.0, -10.0 );
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
	} */

	{
		const Point4d point( 10.0, 10.0, 10.0, 10.0 );
		const Point4d& moved = point + Vector4d( 1.0, 4.0, 0.0, 1.0 );
		BOOST_CHECK( moved == Point4d( 11.0, 14.0, 10.0, 11.0 ) );
	}
}

Point4dTest::~Point4dTest()
{
}