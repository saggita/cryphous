#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include "../CrystalRenderer/Color4d.h"
#include "../CrystalRenderer/FrameBuffer.h"

using namespace Crystal::Renderer;

BOOST_AUTO_TEST_CASE( FRAME_BUFFER_TEST )
{
	const int xSize = 256;
	const int ySize = 256;
	FrameBuffer frameBuffer( xSize, ySize);
	frameBuffer.clear( Color4d(100,100,100, 0));
	for( int x = 0; x < xSize; ++x ) {
		for( int y = 0; y < ySize; ++y ) {
			BOOST_CHECK( frameBuffer.getColor(x,y) == Color4d( 100, 100, 100, 0 ) );
		}
	}
	frameBuffer.setColor( Point2d(2, 2), Color4d( 0, 0, 15 ) );
	//bitmap.draw
	//bitmap.drawQuad( Point2d(10, 10), 2, Color4d( 15, 0, 0) );
	//bitmap.drawPoint( Point2d(5, 5), 5, Color4d( 0, 15, 0 ) );
	//bitmap.drawPoint( Point2d(100, 100), 10, Color4d( 15, 15, 0 ));
	//bitmap.dump();
}