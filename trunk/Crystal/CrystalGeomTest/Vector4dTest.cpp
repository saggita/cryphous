#include "Vector4dTest.h"

#include <boost/test/unit_test.hpp>

#include "../CrystalGeom/Vector4d.h"
#include "../CrystalGeom/Tolerances.h"

#include <cmath>

using namespace Crystal::Geom;


Vector4dTest::Vector4dTest(void)
{
	{
		Vector4d vector( 10.0, 10.0, 10.0, 10.0 );
		const double result = vector.getLengthSquared();
		const double expected = 400.0;
		BOOST_CHECK( result == expected );
	}

	{
		Vector4d vector( 10.0, 0.0, 0.0, 0.0 );
		vector.normalize();
		const Vector4d expected( 1.0, 0.0, 0.0, 0.0 );
		BOOST_CHECK( vector == expected );
	}

	{
		Vector4d vector( 1.0, 0.0, 0.0, 1.0 );
		const Vector4d& result = 10.0 * vector * 5.0;
		const Vector4d expected( 50.0, 0.0, 0.0, 50.0 );
		BOOST_CHECK( result == expected );
	}

	{
		const Vector4d vectorX( 1.0, 0.0, 0.0, 2.0 );
		const Vector4d vectorY( 1.0, 1.0, 0.0, 3.0 );
		const Vector4d expected( 2.0, 1.0, 0.0, 5.0 );
		BOOST_CHECK( expected == (vectorX + vectorY) );
	}

	{
		const Vector4d vectorX( 10.0, 0.0, 5.0, 10.0 );
		const Vector4d vectorY( 1.0, 0.0, 1.0, 2.0 );
		const Vector4d expected( 9.0, 0.0, 4.0, 8.0 );
		BOOST_CHECK( expected == (vectorX - vectorY) );
	}
}

Vector4dTest::~Vector4dTest()
{
}