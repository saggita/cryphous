#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include "../CrystalRenderer/Color4d.h"
#include "../CrystalRenderer/FrameBuffer.h"

using namespace Crystal::Renderer;

BOOST_AUTO_TEST_CASE( FRAME_BUFFER_TEST )
{
	const int xSize = 256;
	const int ySize = 256;
	FrameBuffer buffer( xSize, ySize);
	buffer.clear( Color4d(100,100,100, 0));
	for( int x = 0; x < xSize; ++x ) {
		for( int y = 0; y < ySize; ++y ) {
			BOOST_CHECK( buffer.getColor(Point2d(x,y)) == Color4d( 100, 100, 100, 0 ) );
		}
	}
}