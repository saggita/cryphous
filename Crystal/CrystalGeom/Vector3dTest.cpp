#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include "../CrystalGeom/Vector3d.h"
#include "../CrystalGeom/Matrix3d.h"
#include "../CrystalGeom/Tolerances.h"

#include <cmath>

using namespace Crystal::Geom;

BOOST_AUTO_TEST_CASE( VECTOR_3D_TEST )
{
	{
		Vector3d vector( 10.0, 10.0, 10.0 );
		const float result = vector.getLengthSquared();
		const float expected = 300.0;
		BOOST_CHECK( result == expected );
	}

	{
		Vector3d vector( 10.0, 0.0, 0.0 );
		vector.normalize();
		const Vector3d expected( 1.0, 0.0, 0.0 );
		BOOST_CHECK( vector == expected );
	}

	{
		Vector3d vector( 1.0, 0.0, 0.0 );
		const Vector3d& result = 10.0 * vector * 5.0;
		const Vector3d expected( 50.0, 0.0, 0.0 );
		BOOST_CHECK( result == expected );
	}

	{
		const Vector3d vectorX( 1.0, 0.0, 0.0 );
		const Vector3d vectorY( 0.0, 1.0, 0.0 );
		const Vector3d vectorZ( 0.0, 0.0, 1.0 );
		BOOST_CHECK( vectorX.getOuterProduct( vectorY ) == vectorZ );
		BOOST_CHECK( vectorY.getOuterProduct( vectorZ ) == vectorX );
		BOOST_CHECK( vectorZ.getOuterProduct( vectorX ) == vectorY );
	}

	{
		const Vector3d vectorX( 1.0, 0.0, 0.0 );
		const Vector3d vectorY( 1.0, 1.0, 0.0 );
		const Vector3d expected( 2.0, 1.0, 0.0 );
		BOOST_CHECK( expected == (vectorX + vectorY) );
	}

	{
		const Vector3d vectorX( 10.0, 0.0, 5.0 );
		const Vector3d vectorY( 1.0, 0.0, 1.0 );
		const Vector3d expected( 9.0, 0.0, 4.0 );
		BOOST_CHECK( expected == (vectorX - vectorY) );
	}

	{
		const Matrix3d matrix( 1.0, 1.0, 1.0,
			2.0, 2.0, 2.0,
			3.0, 3.0, 3.0);
		const Vector3d& result = Vector3d( 1.0, 2.0, 3.0).getMult( matrix );
		const Vector3d expected( 14.0, 14.0, 14.0 );
		BOOST_CHECK( result == expected );
	}

	{
		const Matrix3d matrix( 1.0, 1.0, 1.0,
			2.0, 2.0, 2.0,
			3.0, 3.0, 3.0);
		const Vector3d& result = Vector3d( 1.0, 2.0, 3.0) * matrix;
		const Vector3d expected( 14.0, 14.0, 14.0 );
		BOOST_CHECK( result == expected );
	}
}