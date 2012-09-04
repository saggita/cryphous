#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include "../CrystalRenderer/ColorBuffer.h"

using namespace Crystal::Renderer;

BOOST_AUTO_TEST_CASE( COLOR_BUFFER_TEST )
{
	const int xSize = 256;
	const int ySize = 256;
	ColorBuffer buffer( xSize, ySize);
	const Color4d color( 100, 100, 100, 0);
	buffer.clear( color);
	BOOST_CHECK( buffer.getColor( Point2d(0, 0)) == color ); 
	BOOST_CHECK( buffer.getColor( Point2d(100, 100) ) == color );
	BOOST_CHECK( buffer.getColor( Point2d(255, 255) ) == color );
}