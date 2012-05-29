
#include "QuaternionTest.h"

#include <boost/test/unit_test.hpp>

#include "../CrystalGeom/Quaternion.h"
#include "../CrystalGeom/Vector3d.h"
#include "../CrystalGeom/Matrix3d.h"
#include "../CrystalGeom/Tolerances.h"

using namespace Crystal::Geom;

QuaternionTest::QuaternionTest(void)
{
	{
		Quaternion quaternion;
		BOOST_CHECK( quaternion.isNormalized() );
	}

	{
		Quaternion quaternion( Vector3d( 1.0, 0.0, 0.0 ), Tolerances::getPI() );
		const Matrix3d& result = quaternion.getMatrix();
		Matrix3d expected;
		expected.setRotateX( Tolerances::getPI() );
		BOOST_CHECK( result == expected );
	}
	
	{
		Quaternion quaternion( Vector3d( 0.0, 1.0, 0.0 ), Tolerances::getPI() );
		const Matrix3d& result = quaternion.getMatrix();
		Matrix3d expected;
		expected.setRotateY( Tolerances::getPI() );
		BOOST_CHECK( result == expected );
	}

	{
		Quaternion quaternion( Vector3d( 0.0, 0.0, 1.0 ), Tolerances::getPI() );
		const Matrix3d& result = quaternion.getMatrix();
		Matrix3d expected;
		expected.setRotateZ( Tolerances::getPI() );
		BOOST_CHECK( result == expected );
	}
}