#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include "../CrystalRenderer/PointSprite.h"

using namespace Crystal::Renderer;

BOOST_AUTO_TEST_CASE( POINT_SPRITE_TEST )
{
	PointSprite sprite(5, Color4d( 1.0, 1.0, 1.0));
	const FrameBuffer& buffer = sprite.getBuffer();
	BOOST_CHECK( buffer.getColor(Point2d(0,0)) == Color4d( 0.0, 0.0, 0.0 ) );
	BOOST_CHECK_EQUAL( buffer.getDepth(Point2d(0,0)), 1.0e+9f );
	BOOST_CHECK( buffer.getColor(Point2d(5,5)) == Color4d( 1.0, 1.0, 1.0 ) );
	BOOST_CHECK_EQUAL( buffer.getDepth(Point2d(5,5)), 5.0f );
	BOOST_CHECK_EQUAL( sprite.getRadius(), 5 );
}