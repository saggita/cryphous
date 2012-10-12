#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include "../CrystalGeom/Matrix4d.h"
#include "../CrystalGeom/Matrix3d.h"

using namespace Crystal::Geom;

BOOST_AUTO_TEST_CASE(MATRIX_4D_TEST)
{
	{
		Matrix4d matrix( 0.0, 0.0, 0.0, 0.0,
			0.0, 0.0, 0.0, 0.0,
			0.0, 0.0, 0.0, 0.0,
			0.0, 0.0, 0.0, 0.0);
		BOOST_CHECK( matrix.isZero() );
	}

	{
		Matrix4d matrix( 0.0, 0.0, 0.0, 1.0,
			0.0, 0.0, 0.0, 0.0,
			0.0, 0.0, 0.0, 0.0,
			0.0, 0.0, 0.0, 0.0);
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
			0.0, 0.0, 0.0, 0.0);
		BOOST_CHECK( !matrix.isIdentity() );
	}

	{
		Matrix4d matrixX( 1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0 );
		Matrix4d matrixY( 1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0 );
		Matrix4d expected( 1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0 );
		BOOST_CHECK( matrixX.getProduct( matrixY ) == expected  );
		BOOST_CHECK( matrixX * matrixY == expected );
		BOOST_CHECK( (matrixX *= matrixY) == expected );
	}
	
	{
		const Matrix4d matrixX( 
			1.0, 1.0, 1.0, 1.0,
			2.0, 2.0, 2.0, 2.0,
			3.0, 3.0, 3.0, 3.0,
			4.0, 4.0, 4.0, 4.0 );
		Matrix4d matrixY(
			1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0 );
		const Matrix4d expected( 
			1.0, 1.0, 1.0, 1.0,
			2.0, 2.0, 2.0, 2.0,
			3.0, 3.0, 3.0, 3.0,
			4.0, 4.0, 4.0, 4.0 );
		const Matrix4d& result = matrixX.getProduct(matrixY);
		BOOST_CHECK( matrixX.getProduct( matrixY ) == expected  );
		BOOST_CHECK( matrixX * matrixY == expected );
	}

	{
		const Matrix4d matrixX(
			1.0, 1.0, 1.0, 1.0,
			2.0, 2.0, 2.0, 2.0,
			3.0, 3.0, 3.0, 3.0,
			4.0, 4.0, 4.0, 4.0 );
		const Matrix4d matrixY(
			1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0
			);
		const Matrix4d expected( 1.0, 1.0, 1.0, 1.0,
			2.0, 2.0, 2.0, 2.0,
			3.0, 3.0, 3.0, 3.0,
			4.0, 4.0, 4.0, 4.0);
		BOOST_CHECK( matrixX * matrixY == expected  );
	}
}

BOOST_AUTO_TEST_CASE( MATRIX_3D_TEST_ROTATION )
{
	Matrix4d matrix4d;
	matrix4d.setRotateX( Tolerances::getPI() );

	Matrix3d matrix3d;
	matrix3d.setRotateX( Tolerances::getPI() );

	BOOST_CHECK( matrix4d.x00 == matrix3d.x00 );
	BOOST_CHECK( matrix4d.x01 == matrix3d.x01 );
	BOOST_CHECK( matrix4d.x02 == matrix3d.x02 );

	BOOST_CHECK( matrix4d.x10 == matrix3d.x10 );
	BOOST_CHECK( matrix4d.x11 == matrix3d.x11 );
	BOOST_CHECK( matrix4d.x12 == matrix3d.x12 );
	
	BOOST_CHECK( matrix4d.x20 == matrix3d.x20 );
	BOOST_CHECK( matrix4d.x21 == matrix3d.x21 );
	BOOST_CHECK( matrix4d.x22 == matrix3d.x22 );

	BOOST_CHECK( !matrix4d.isZero() );
	BOOST_CHECK( !matrix4d.isIdentity() );

	matrix4d.setIdentity();
	BOOST_CHECK( !matrix4d.isZero() );
	BOOST_CHECK( matrix4d.isIdentity() );	
}