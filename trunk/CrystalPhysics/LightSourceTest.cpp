#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include "../CrystalPhysics/LightSource.h"

#include "../CrystalGeom/Vector3d.h"

using namespace Crystal::Geom;
using namespace Crystal::Physics;

BOOST_AUTO_TEST_CASE(LIGHT_SOURCE_TEST)
{
	LightSource light(0, Vector3d( 1.0, 0.0, 0.0 ) );
	light.integrateTime( 0.01f );
}
