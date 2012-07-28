#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include "../CrystalRenderer/Color4d.h"
#include "../CrystalRenderer/PixelMap.h"

using namespace Crystal::Renderer;

BOOST_AUTO_TEST_CASE( PIXEL_MAP_TEST )
{
	const int xSize = 256;
	const int ySize = 256;
	Bitmap bitmap( xSize, ySize);
	bitmap.clear( Color4d(100,100,100, 0));
	for( int x = 0; x < xSize; ++x ) {
		for( int y = 0; y < ySize; ++y ) {
			BOOST_CHECK( bitmap.getColor(x,y) == Color4d( 100, 100, 100, 0 ) );
		}
	}
	bitmap.setColor( Point3d(2, 2, 10), Color4d( 0, 0, 15 ) );
	bitmap.drawQuad( Point3d(10, 10, 20), 2, Color4d( 15, 0, 0) );
	bitmap.drawPoint( Point3d(5, 5, 10), 5, Color4d( 0, 15, 0 ) );
	bitmap.drawPoint( Point3d(100, 100, 100), 10, Color4d( 15, 15, 0 ));
	//bitmap.dump();
}