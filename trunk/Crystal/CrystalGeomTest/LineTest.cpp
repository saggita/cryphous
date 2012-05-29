#include "LineTest.h"

#include "../CrystalGeom/Line.h"

#include <boost/test/unit_test.hpp>

using namespace Crystal::Geom;

LineTest::LineTest(void)
{
	getStartTest();
	getEndTest();
	getLengthTest();
	getDirectionTest();
	equalsTest();
}

LineTest::~LineTest(void)
{
}

void LineTest::getStartTest()
{
	const Point3d start( 2.0, 3.0, 4.0 );
	const Point3d end( 5.0, 6.0, 7.0 );
	Line line( start, end );

	BOOST_CHECK( start == line.getStart() );
}

void LineTest::getEndTest()
{
	const Point3d start( 2.0, 3.0, 4.0 );
	const Point3d end( 5.0, 6.0, 7.0 );
	Line line( start, end );

	BOOST_CHECK( start == line.getStart() );

}

void LineTest::getLengthTest()
{
	const Point3d start( 2.0, 3.0, 4.0 );
	const Point3d end( 3.0, 3.0, 4.0 );
	Line line( start, end );

	BOOST_CHECK( line.getLength() == 1.0 );
}

void LineTest::getDirectionTest()
{
	const Point3d start( 2.0, 3.0, 4.0 );
	const Point3d end( 5.0, 6.0, 7.0 );
	Line line( start, end );

	BOOST_CHECK( line.getDirection() == Vector3d( 3.0, 3.0, 3.0) );
}

void LineTest::equalsTest()
{
	Line lineX( Point3d( 1.0, 1.0, 1.0), Point3d( 2.0, 2.0, 2.0) );
	Line lineY( Point3d( 1.0, 1.0, 1.0), Point3d( 2.0, 2.0, 2.0) );
	BOOST_CHECK( lineX.equals( lineY ) );
	BOOST_CHECK( lineX == lineY );
	Line lineZ( Point3d( 1.0, 1.0, 1.0), Point3d( 2.1, 2.0, 2.0) );
	BOOST_CHECK( !lineX.equals( lineZ ) );
	BOOST_CHECK( lineX != lineZ );
}