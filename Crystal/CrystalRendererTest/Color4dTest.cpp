#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include "../CrystalRenderer/Color4d.h"

using namespace Crystal::Renderer;

BOOST_AUTO_TEST_CASE( COLOR4D_TEST )
{
	Color4d black(0, 0, 0);
	Color4d white(255, 255, 255);
	BOOST_CHECK( white != black );
}