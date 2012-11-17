#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include "../CrystalPhysics/LightSourceFactory.h"

#include "../CrystalGeom/Vector3d.h"

using namespace Crystal::Geom;
using namespace Crystal::Physics;

BOOST_AUTO_TEST_CASE(LIGHT_SOURCE_FACTORY_TEST)
{
	LightSourceFactory factory;
	LightSource* light = factory.createLightSource( Vector3d(0.0f, 0.0f, 0.0f ), 100, 1.0f );
	light->integrateTime( 0.01f );
}
