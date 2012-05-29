#include "PrimitiveTest.h"

#include <boost/test/unit_test.hpp>

#include "../CrystalGeom/Primitive.h"

using namespace Crystal::Geom;

PrimitiveTest::PrimitiveTest(void)
{
	Primitive primitive( Point3d( 10.0, 20.0, 30.0 ), Point3d( 20.0, 40.0, 60.0 ), Primitive::Cylinder );
	BOOST_CHECK( primitive.getCenter() == Point3d( 15.0, 30.0, 45.0 ) );
	BOOST_CHECK( primitive.getMin() == Point3d( 10.0, 20.0, 30.0 ) );
	BOOST_CHECK( primitive.getMax() == Point3d( 20.0, 40.0, 60.0 ) );
	BOOST_CHECK( primitive.getType() == Primitive::Cylinder );
	
	primitive.move( Vector3d( 15.0, 0.0, 5.0 ) );
	BOOST_CHECK( primitive.getCenter() == Point3d( 30.0, 30.0, 50.0 ) );
	BOOST_CHECK( primitive.getMin() == Point3d( 25.0, 20.0, 35.0 ) );
	BOOST_CHECK( primitive.getMax() == Point3d( 35.0, 40.0, 65.0 ) );

	Primitive* clone = primitive.createClone();
	delete clone;
}
