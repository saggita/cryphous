#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include "../CrystalRenderer/PointSprite.h"

using namespace Crystal::Renderer;

BOOST_AUTO_TEST_CASE( POINT_SPRITE_TEST )
{
	PointSprite sprite(5);
}