#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

//#include "../CrystalGeom/Matrix4d.h"

//using namespace Crystal::Geom;

/*BOOST_AUTO_TEST_CASE(MATRIX_4D_TEST)
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
}*/