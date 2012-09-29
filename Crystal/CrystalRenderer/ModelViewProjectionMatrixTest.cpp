#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include "../CrystalGeom/Matrix3d.h"

#include "../CrystalRenderer/ModelViewProjectionMatrix.h"

using namespace Crystal::Geom;
using namespace Crystal::Renderer;

BOOST_AUTO_TEST_CASE( MODEL_VIEW_PROJECTION_MATRIX_TEST )
{
	ModelViewProjectionMatrix mvpMatrix;
	mvpMatrix.setRotateX( Tolerances::getPI() );

	Matrix3d matrix3d;
	matrix3d.setRotateX( Tolerances::getPI() );

	BOOST_CHECK( mvpMatrix.x00 == matrix3d.x00 );
	BOOST_CHECK( mvpMatrix.x01 == matrix3d.x01 );
	BOOST_CHECK( mvpMatrix.x02 == matrix3d.x02 );

	BOOST_CHECK( mvpMatrix.x10 == matrix3d.x10 );
	BOOST_CHECK( mvpMatrix.x11 == matrix3d.x11 );
	BOOST_CHECK( mvpMatrix.x12 == matrix3d.x12 );
	
	BOOST_CHECK( mvpMatrix.x20 == matrix3d.x20 );
	BOOST_CHECK( mvpMatrix.x21 == matrix3d.x21 );
	BOOST_CHECK( mvpMatrix.x22 == matrix3d.x22 );

	BOOST_CHECK( !mvpMatrix.isZero() );
	BOOST_CHECK( !mvpMatrix.isIdentity() );

	mvpMatrix.setIdentity();
	BOOST_CHECK( !mvpMatrix.isZero() );
	BOOST_CHECK( mvpMatrix.isIdentity() );	
}

BOOST_AUTO_TEST_CASE( MODEL_VIEW_PROJECTION_MATRIX_TEST_ORTHOGONAL_VIEW )
{
	ModelViewProjectionMatrix matrix;
	matrix.setOrthogonalViewMatrix( -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
	Matrix4d expected(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, -1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
	BOOST_CHECK( matrix == expected );
}

BOOST_AUTO_TEST_CASE( MODEL_VIEW_PROJECTION_MATRIX_TEST_PERSPECTIVE_VIEW )
{
	ModelViewProjectionMatrix matrix;
	matrix.setPerspectiveViewMatrix( -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
	Matrix4d expected(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, -0.5f, 0.5f,
		0.0f, 0.0f, -1.0f, 1.0f );
	BOOST_CHECK( matrix == expected );
}