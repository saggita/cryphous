#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include "../CrystalRenderer/PointSpriteRenderer.h"

#include "Bitmap.h"

using namespace Crystal::Renderer;

BOOST_AUTO_TEST_CASE( POINT_SPRITE_RENDERER_TEST )
{
	FrameBuffer buffer(256, 256);
	PointSprite sprite(5, Color4d(0.0, 0.0, 1.0));
	PointSpriteRenderer renderer( buffer);
	renderer.render( sprite, Point2d(10,10));
	BOOST_CHECK( buffer.getColor(Point2d(10,10)) == Color4d(0.0, 0.0,1.0) );

	Image image( 256, 256 );
	
	for(unsigned int i=0; i<image.height; i++){
		for(unsigned int j=0; j<image.width; j++){
			image.colors[(image.height - i - 1)*image.width + j].b = buffer.getColor(Point2d(i,j)).blue * 255;
			image.colors[(image.height - i - 1)*image.width + j].g = buffer.getColor(Point2d(i,j)).green * 255;
			image.colors[(image.height - i - 1)*image.width + j].r = buffer.getColor(Point2d(i,j)).red * 255;
		}
	}
	image.dump("../PointSpriteRendererTest.bmp");
}