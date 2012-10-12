#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include "../CrystalRenderer/MVPMatrixSetter.h"

using namespace Crystal::Geom;
using namespace Crystal::Renderer;


BOOST_AUTO_TEST_CASE( MVP_MATRIX_SETTER_TEST_ORTHOGONAL_VIEW )
{
	Matrix4d matrix = MVPMatrixSetter::getOrthogonalViewMatrix(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
	Matrix4d expected(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, -1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
	BOOST_CHECK( matrix == expected );
}

BOOST_AUTO_TEST_CASE( MVP_MATRIX_SETTER_TEST_PERSPECTIVE_VIEW )
{
	Matrix4d matrix = MVPMatrixSetter::getPerspectiveViewMatrix( -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
	Matrix4d expected(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, -0.5f, 0.5f,
		0.0f, 0.0f, -1.0f, 1.0f );
	BOOST_CHECK( matrix == expected );
}