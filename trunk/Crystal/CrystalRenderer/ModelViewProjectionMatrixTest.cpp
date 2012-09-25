#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include "../CrystalRenderer/ModelViewProjectionMatrix.h"

using namespace Crystal::Geom;
using namespace Crystal::Renderer;

BOOST_AUTO_TEST_CASE( MODEL_VIEW_PROJECTION_MATRIX_TEST )
{
	ModelViewProjectionMatrix matrix;
	matrix.setRotateX( -90.0f * Tolerances::getPI() / 180.0f );
}