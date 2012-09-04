#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include "../CrystalRenderer/NormalBuffer.h"

using namespace Crystal::Geom;
using namespace Crystal::Renderer;

BOOST_AUTO_TEST_CASE( NORMAL_BUFFER_TEST )
{
	const int xSize = 256;
	const int ySize = 256;
	NormalBuffer buffer( xSize, ySize);
	Vector3d normal( 0.0f, 1.0f, 0.0f );
	buffer.clear( normal );
	BOOST_CHECK( buffer.getNormal(Point2d(0,0)) == normal );
	BOOST_CHECK( buffer.getNormal(Point2d(100,100)) == normal );
	BOOST_CHECK( buffer.getNormal(Point2d(255,255)) == normal );
}