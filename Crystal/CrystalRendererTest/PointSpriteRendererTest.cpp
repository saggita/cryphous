#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include "../CrystalRenderer/PointSpriteRenderer.h"

using namespace Crystal::Renderer;

BOOST_AUTO_TEST_CASE( POINT_SPRITE_RENDERER_TEST )
{
	FrameBuffer buffer(256, 256);
	PointSprite sprite(5, Color4d(0.0, 0.0, 1.0));
	PointSpriteRenderer renderer( buffer);
	renderer.render( sprite, Point2d(10,10));
	BOOST_CHECK( buffer.getColor(Point2d(10,10)) == Color4d(0.0, 0.0,1.0) );
}