#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include "../CrystalRenderer/PointSpriteFactory.h"

using namespace Crystal::Renderer;

BOOST_AUTO_TEST_CASE( POINT_SPRITE_FACTORY_TEST )
{
	PointSpriteFactory factory(50);
	BOOST_CHECK_EQUAL( factory.getPointSprites().size(), 50);
}