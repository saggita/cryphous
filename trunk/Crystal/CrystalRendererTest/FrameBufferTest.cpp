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
	const Color4d color(100, 100, 100, 0 );
	buffer.clear( color);

	BOOST_CHECK( buffer.getColor(Point2d(0,0)) == color );
	BOOST_CHECK( buffer.getColor(Point2d(100,100)) == color );
	BOOST_CHECK( buffer.getColor(Point2d(255,255)) == color );
	
	BOOST_CHECK( buffer.isValidPointX( Point2d(0, 100 ) ) );
	BOOST_CHECK( buffer.isValidPointY( Point2d(0, 100 ) ) );
	BOOST_CHECK( buffer.isInvalidPointX( Point2d(-1, 100) ) );
	BOOST_CHECK( buffer.isInvalidPointY( Point2d(100, 512 ) ) );
	BOOST_CHECK( buffer.isValidPoint( Point2d( 100, 100 ) ) );
	BOOST_CHECK( buffer.isInvalidPoint( Point2d( 512, 100 ) ) );
}