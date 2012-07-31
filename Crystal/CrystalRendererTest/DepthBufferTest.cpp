#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include "../CrystalRenderer/DepthBuffer.h"

using namespace Crystal::Renderer;

BOOST_AUTO_TEST_CASE( DEPTH_BUFFER_TEST )
{
	const int xSize = 256;
	const int ySize = 256;
	DepthBuffer buffer( xSize, ySize);
	buffer.clear( 100.0f );
	for( int x = 0; x < xSize; ++x ) {
		for( int y = 0; y < ySize; ++y ) {
			BOOST_CHECK( buffer.getDepth(Point2d(x,y)) == 100.0f );
		}
	}
}