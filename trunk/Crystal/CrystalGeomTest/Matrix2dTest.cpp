#include "Matrix2dTest.h"

#include <boost/test/unit_test.hpp>

#include "../CrystalGeom/Matrix2d.h"
#include "../CrystalGeom/Vector2d.h"

using namespace Crystal::Geom;

Matrix2dTest::Matrix2dTest(void)
{
	{
		Matrix2d matrix( 0.0, 0.0,
			0.0, 0.0);
		BOOST_CHECK( matrix.isZero() );
	}

	{
		Matrix2d matrix( 0.0, 1.0,
			0.0, 0.0);
		BOOST_CHECK( !matrix.isZero() );
	}

	{
		Matrix2d matrix( 1.0, 0.0,
			0.0, 1.0 );
		BOOST_CHECK( matrix.isIdentity() );
	}

	{
		Matrix2d matrix( 1.0, 1.0,
			1.0, 1.0 );
		BOOST_CHECK( !matrix.isIdentity() );
	}

	{
		Matrix2d matrixX( 1.0, 0.0,
			0.0, 1.0 );
		Matrix2d matrixY( 1.0, 0.0,
			0.0, 1.0 );
		const Matrix2d& result = matrixX.getProduct( matrixY );
		BOOST_CHECK( result.isIdentity() );
	}

	{
		Matrix2d matrixX( 1.0, 0.0,
			0.0, 1.0 );
		Matrix2d matrixY( 1.0, 0.0,
			0.0, 1.0 );
		const Matrix2d& result = matrixX * matrixY;
		BOOST_CHECK( result.isIdentity() );
	}

	{
		Matrix2d matrixX( 1.0, 0.0,
			0.0, 1.0 );
		Matrix2d matrixY( 0.0, 0.0,
			0.0, 0.0 );
		const Matrix2d& result = matrixX.getProduct( matrixY );
		BOOST_CHECK( result.isZero() );
	}

	{
		Matrix2d matrixX( 1.0, 0.0,
			0.0, 1.0 );
		Matrix2d matrixY( 0.0, 0.0,
			0.0, 0.0 );
		matrixX *= matrixY;
		BOOST_CHECK( matrixX.isZero() );
	}

	{
		Matrix2d matrix( 1.0, 2.0,
			3.0, 4.0 );
		const Matrix2d& inverse = matrix.getInverse();
		const Matrix2d& result = matrix.getProduct( inverse );
		BOOST_CHECK( result.isIdentity() );
	}

	{
		Matrix2d matrix( 1.0, 1.0,
			1.0, 1.0 );
		BOOST_CHECK_EQUAL( matrix.getDeterminant(), 0.0 );
	}

	{
		Matrix2d matrix( 1.0, 0.0,
			0.0, 1.0 );
		BOOST_CHECK_EQUAL( matrix.getDeterminant(), 1.0 );
	}

	{
		Matrix2d matrix( 1.0, 2.0, 3.0, 4.0 );
		BOOST_CHECK( matrix.getTranspose() == Matrix2d( 1.0, 3.0, 2.0, 4.0 ) );
	}

	{
		Matrix2d matrixX( 1.0, 2.0, 3.0, 4.0 );
		Matrix2d matrixY( 2.0, 3.0, 4.0, 5.0 );
		BOOST_CHECK( matrixX.getAdd( matrixY ) == Matrix2d( 3.0, 5.0, 7.0, 9.0 ) );
		BOOST_CHECK( (matrixX + matrixY) == Matrix2d( 3.0, 5.0, 7.0, 9.0 ) );
	}

	{
		const Matrix2d matrix( 1.0, 1.0,
			2.0, 2.0 );
		const Vector2d& result = matrix.getMult( Vector2d( 1.0, 2.0 ) );
		const Vector2d expected = Vector2d( 3.0, 6.0 );
		BOOST_CHECK( result == expected );
	}

	{
		const Matrix2d matrix( 1.0, 1.0,
			2.0, 2.0 );
		const Vector2d& result = matrix * Vector2d( 1.0, 2.0 );
		const Vector2d expected =  Vector2d( 3.0, 6.0 );
		BOOST_CHECK( result == expected );
	}
}