#include "Matrix4dTest.h"

#include <boost/test/unit_test.hpp>

#include "../CrystalGeom/Matrix4d.h"

using namespace Crystal::Geom;

Matrix4dTest::Matrix4dTest(void)
{
	{
		Matrix4d matrix( 0.0, 0.0, 0.0, 0.0,
			0.0, 0.0, 0.0, 0.0,
			0.0, 0.0, 0.0, 0.0,
			0.0, 0.0, 0.0, 0.0);
		BOOST_CHECK( matrix.isZero() );
	}

	{
		Matrix4d matrix( 0.0, 0.0, 1.0, 1.0,
			0.0, 0.0, 0.0, 0.0,
			0.0, 0.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 1.0);
		BOOST_CHECK( !matrix.isZero() );
	}

	{
		Matrix4d matrix( 1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0);
		BOOST_CHECK( matrix.isIdentity() );
	}

	{
		Matrix4d matrix( 1.0, 1.0, 0.0, 0.0,
			1.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 0.0, 0.0,
			0.0, 0.0, 0.0, 1.0);
		BOOST_CHECK( !matrix.isIdentity() );
	}
}