#include "Space3dTest.h"

#include "../CrystalGeom/Space3d.h"
#include "../CrystalGeom/Vector3d.h"

#include <boost/test/unit_test.hpp>

using namespace Crystal::Geom;

Space3dTest::Space3dTest(void)
{
	{
		Space3d space(Vector3d(1.0, 0.0, 0.0), Vector3d( 0.0, 1.0, 0.0), Vector3d( 0.0, 0.0, 1.0) );
		BOOST_CHECK( space.isRightHanded() );
	}

	{
		Space3d space(Vector3d(1.0, 0.0, 0.0), Vector3d( 0.0, 1.0, 0.0), Vector3d( 0.0, 0.0, -1.0) );
		BOOST_CHECK( space.isLeftHanded() );
	}

	{
		Space3d space(Vector3d(1.0, 0.0, 0.0), Vector3d( 0.0, 1.0, 0.0), Vector3d( 0.0, 1.0, 1.0 ) );
		BOOST_CHECK( !space.isValid() );
	}

	{
		Space3d space(Vector3d(1.0, 0.0, 0.0), Vector3d(0.0, 1.0, 0.0));
		BOOST_CHECK( space.isValid() );
		BOOST_CHECK( space.isRightHanded() );
	}
}

Space3dTest::~Space3dTest(void)
{
}