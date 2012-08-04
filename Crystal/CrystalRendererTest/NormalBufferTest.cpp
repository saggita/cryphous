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
	buffer.clear( Vector3d( 0.0f, 1.0f, 0.0f ) );
	for( int x = 0; x < xSize; ++x ) {
		for( int y = 0; y < ySize; ++y ) {
			BOOST_CHECK( buffer.getNormal(Point2d(x,y)) == Vector3d( 0.0f, 1.0f, 0.0f ) );
		}
	}
}