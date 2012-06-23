#include "BoxTest.h"

#include <boost/test/unit_test.hpp>

#include "../CrystalGeom/Box.h"
#include "../CrystalGeom/Vector3d.h"
#include "../CrystalGeom/Tolerances.h"

using namespace Crystal::Geom;

BoxTest::BoxTest(void)
{
	{
		Box box( Vector3d( 10.0, 20.0, 30.0), Vector3d( 30.0, 20.0, 10.0) );
		BOOST_CHECK( box.getMax() == Vector3d( 30.0, 20.0, 30.0) );
		BOOST_CHECK( box.getMin() == Vector3d( 10.0, 20.0, 10.0) );
	}

	{
		Box box( Vector3d( 10.0, 20.0, 30.0), Vector3d( 30.0, 10.0, 10.0) );
		const Vector3d pointX( 15.0, 15.0, 15.0 );
		const Vector3d pointY( 40.0, 15.0, 15.0 );
		BOOST_CHECK( box.isInterior( pointX ) );
		BOOST_CHECK( !box.isInterior( pointY ) );
		BOOST_CHECK( !box.isExterior( pointX ) );
		BOOST_CHECK( box.isExterior( pointY ) );
	}

	{
		Box box( Vector3d( 10.0, 20.0, 30.0), Vector3d( 30.0, 10.0, 10.0) );
		const Box& outerBox = box.getOuterOffset( 1.0 );
		BOOST_CHECK( box.getVolume() < outerBox.getVolume() );
		const Box& innerBox = box.getInnerOffset( 1.0 );
		BOOST_CHECK( box.getVolume() > innerBox.getVolume() );
	}

	{
		Box box( Vector3d( 10.0, 20.0, 30.0), Vector3d( 30.0, 10.0, 10.0 ) );
		BOOST_CHECK( box.getCenter() == Vector3d( 20.0, 15.0, 20.0 ) );
	}
}
