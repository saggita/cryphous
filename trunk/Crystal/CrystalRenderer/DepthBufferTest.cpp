#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include "../CrystalRenderer/DepthBuffer.h"

using namespace Crystal::Renderer;

BOOST_AUTO_TEST_CASE( DEPTH_BUFFER_TEST )
{
	const int xSize = 256;
	const int ySize = 256;
	DepthBuffer buffer( xSize, ySize);
	const float depth = 100.0f;
	buffer.clear( depth );
	BOOST_CHECK( buffer.getDepth(Point2d(0,0)) == depth );
	BOOST_CHECK( buffer.getDepth(Point2d(100,100)) == depth );
	BOOST_CHECK( buffer.getDepth(Point2d(255,255)) == depth );
}