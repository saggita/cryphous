#define BOOST_TEST_NO_LIB
#include <boost/test/included/unit_test.hpp>

#include "../CrystalGeom/Vector3d.h"
#include "../CrystalGeom/Matrix3d.h"

using namespace Crystal::Geom;

BOOST_AUTO_TEST_CASE(MATRIX_3D_TEST)
{
	{
		Matrix3d matrix( 0.0, 0.0, 0.0,
			0.0, 0.0, 0.0,
			0.0, 0.0, 0.0);
		BOOST_CHECK( matrix.isZero() );
	}

	{
		Matrix3d matrix( 0.0, 0.0, 1.0,
			0.0, 0.0, 0.0,
			0.0, 0.0, 0.0);
		BOOST_CHECK( !matrix.isZero() );
	}

	{
		Matrix3d matrix( 1.0, 0.0, 0.0,
			0.0, 1.0, 0.0,
			0.0, 0.0, 1.0);
		BOOST_CHECK( matrix.isIdentity() );
	}

	{
		Matrix3d matrix( 1.0, 1.0, 0.0,
			1.0, 1.0, 0.0,
			0.0, 0.0, 0.0);
		BOOST_CHECK( !matrix.isIdentity() );
	}

	{
		Matrix3d matrix( 1.0, 0.0, 0.0,
			0.0, 1.0, 0.0,
			0.0, 0.0, 1.0 );
		BOOST_CHECK_EQUAL( matrix.getDeterminant(), 1.0 );
	}

	{
		Matrix3d matrix( 1.0, 0.0, 0.0,
			0.0, 1.0, 0.0,
			0.0, 0.0, 1.0);
		Matrix3d identity( 1.0, 0.0, 0.0,
			0.0, 1.0, 0.0,
			0.0, 0.0, 1.0 );
		BOOST_CHECK( matrix.getInverse() == identity );
	}

	{
		Matrix3d matrixX( 1.0, 0.0, 0.0,
			0.0, 1.0, 0.0,
			0.0, 0.0, 1.0 );
		Matrix3d matrixY( 1.0, 0.0, 0.0,
			0.0, 1.0, 0.0,
			0.0, 0.0, 1.0 );
		Matrix3d expected( 1.0, 0.0, 0.0,
			0.0, 1.0, 0.0,
			0.0, 0.0, 1.0 );
		BOOST_CHECK( matrixX.getProduct( matrixY ) == expected  );
		BOOST_CHECK( matrixX * matrixY == expected );
		BOOST_CHECK( (matrixX *= matrixY) == expected );
	}
	
	{
		const Matrix3d matrixX( 
			1.0, 1.0, 1.0,
			2.0, 2.0, 2.0,
			3.0, 3.0, 3.0 );
		const Matrix3d matrixY( 
			4.0, 4.0, 4.0,
			5.0, 5.0, 5.0,
			6.0, 6.0, 6.0 );
		const Matrix3d expected( 15.0, 15.0, 15.0,
			30.0, 30.0, 30.0,
			45.0, 45.0, 45.0 );
		const Matrix3d& result = matrixX.getProduct(matrixY);
		BOOST_CHECK( matrixX.getProduct( matrixY ) == expected  );
		BOOST_CHECK( matrixX * matrixY == expected );
	}

	{
		const Matrix3d matrixX( 1.0, 1.0, 1.0,
			2.0, 2.0, 2.0,
			3.0, 3.0, 3.0 );
		const Matrix3d matrixY( 4.0, 4.0, 4.0,
			5.0, 5.0, 5.0,
			6.0, 6.0, 6.0 );
		const Matrix3d expected( 15.0, 15.0, 15.0,
			30.0, 30.0, 30.0,
			45.0, 45.0, 45.0 );
		BOOST_CHECK( matrixX * matrixY == expected  );
	}

	{
		const Matrix3d matrix( 1.0, 2.0, 2.0,
			1.0, 1.0, 5.0,
			1.0, 2.0, 1.0);
		const Matrix3d identity( 1.0, 0.0, 0.0,
			0.0, 1.0, 0.0,
			0.0, 0.0, 1.0 );
		const Matrix3d& inverse = matrix.getInverse();
		BOOST_CHECK( identity == matrix.getProduct( inverse ) );
	}
}