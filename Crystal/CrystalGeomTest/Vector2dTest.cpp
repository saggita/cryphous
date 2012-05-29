#include "Vector2dTest.h"

#include <boost/test/unit_test.hpp>

#include "../CrystalGeom/Vector2d.h"
#include "../CrystalGeom/Matrix2d.h"
#include "../CrystalGeom/Tolerances.h"

#include <cmath>

using namespace Crystal::Geom;


Vector2dTest::Vector2dTest(void)
{
	{
		Vector2d vector( 10.0, 10.0 );
		const double result = vector.getLengthSquared();
		const double expected = 200.0;
		BOOST_CHECK( result == expected );
	}

	{
		Vector2d vector( 10.0, 0.0 );
		vector.normalize();
		const Vector2d expected( 1.0, 0.0 );
		BOOST_CHECK( vector == expected );
	}

	{
		Vector2d vector( 1.0, 0.0 );
		const Vector2d& result = 10.0 * vector * 5.0;
		const Vector2d expected( 50.0, 0.0 );
		BOOST_CHECK( result == expected );
	}

	{
		const Vector2d vectorX( 1.0, 0.0 );
		const Vector2d vectorY( 1.0, 1.0 );
		const Vector2d expected( 2.0, 1.0 );
		BOOST_CHECK( expected == (vectorX + vectorY) );
	}

	{
		const Vector2d vectorX( 10.0, 5.0 );
		const Vector2d vectorY( 1.0, 1.0 );
		const Vector2d expected( 9.0, 4.0 );
		BOOST_CHECK( expected == (vectorX - vectorY) );
	}

	{
		const Matrix2d matrix( 1.0, 1.0,
			2.0, 2.0 );
		const Vector2d result = Vector2d( 1.0, 2.0 ) * matrix;
		const Vector2d expected( 5.0, 5.0);
		BOOST_CHECK( expected == result );
	}
}

Vector2dTest::~Vector2dTest()
{
}