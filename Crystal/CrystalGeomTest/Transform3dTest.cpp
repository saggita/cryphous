#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include "../CrystalGeom/Transform3d.h"

using namespace Crystal::Geom;

BOOST_AUTO_TEST_CASE(TRANSFORM_3D_TEST)
{
	const Matrix3d matrix( 
		1.0, 1.0, 1.0,
		2.0, 2.0, 2.0,
		3.0, 3.0, 3.0 );
	const Vector3d& result = matrix * Vector3d( 1.0, 2.0, 3.0 );
	const Vector3d expected =  Vector3d( 6.0, 12.0, 18.0 );
	BOOST_CHECK( result == expected );
}