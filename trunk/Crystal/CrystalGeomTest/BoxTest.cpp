#include "BoxTest.h"

#include <boost/test/unit_test.hpp>

#include "../CrystalGeom/Box.h"
#include "../CrystalGeom/Point3d.h"
#include "../CrystalGeom/Tolerances.h"

using namespace Crystal::Geom;

BoxTest::BoxTest(void)
{
	{
		Box box( Point3d( 10.0, 20.0, 30.0), Point3d( 30.0, 20.0, 10.0) );
		BOOST_CHECK( box.getMax() == Point3d( 30.0, 20.0, 30.0) );
		BOOST_CHECK( box.getMin() == Point3d( 10.0, 20.0, 10.0) );
	}

	{
		Box box( Point3d( 10.0, 20.0, 30.0), Point3d( 30.0, 10.0, 10.0) );
		const Point3d pointX( 15.0, 15.0, 15.0 );
		const Point3d pointY( 40.0, 15.0, 15.0 );
		BOOST_CHECK( box.isInterior( pointX ) );
		BOOST_CHECK( !box.isInterior( pointY ) );
		BOOST_CHECK( !box.isExterior( pointX ) );
		BOOST_CHECK( box.isExterior( pointY ) );
	}

	{
		Box box( Point3d( 10.0, 20.0, 30.0), Point3d( 30.0, 10.0, 10.0) );
		const Box& outerBox = box.getOuterOffset( 1.0 );
		BOOST_CHECK( box.getVolume() < outerBox.getVolume() );
		const Box& innerBox = box.getInnerOffset( 1.0 );
		BOOST_CHECK( box.getVolume() > innerBox.getVolume() );
	}

	{
		Box box( Point3d( 10.0, 20.0, 30.0), Point3d( 30.0, 10.0, 10.0 ) );
		BOOST_CHECK( box.getCenter() == Point3d( 20.0, 15.0, 20.0 ) );
	}
}
