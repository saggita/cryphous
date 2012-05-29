#include "LoopTest.h"

#include "../CrystalGeom/Loop.h"
#include "../CrystalGeom/Point3d.h"

#include <boost/test/unit_test.hpp>

using namespace Crystal::Geom;

LoopTest::LoopTest(void)
{
	isValidTest();
	isClosedTest();
	isOpenTest();
	closeTest();
	openTest();
}

LoopTest::~LoopTest(void)
{
}

void LoopTest::isValidTest()
{
	std::vector< Point3d > points;
	points.push_back( Point3d( 0.0, 0.0, 0.0 ) );
	points.push_back( Point3d( 1.0, 0.0, 0.0 ) );
	Loop loop( points );
	BOOST_CHECK( loop.isValid() );
}

void LoopTest::isClosedTest()
{
	std::vector< Point3d > points;
	points.push_back( Point3d( 0.0, 0.0, 0.0 ) );
	points.push_back( Point3d( 1.0, 0.0, 0.0 ) );
	Loop loop( points );
	BOOST_CHECK( loop.isOpen() );
}

void LoopTest::isOpenTest()
{
	std::vector< Point3d > points;
	points.push_back( Point3d( 0.0, 0.0, 0.0 ) );
	points.push_back( Point3d( 1.0, 0.0, 0.0 ) );
	points.push_back( Point3d( 1.0, 1.0, 0.0 ) );
	points.push_back( Point3d( 0.0, 0.0, 0.0 ) );
	Loop loop( points );
	BOOST_CHECK( loop.isClosed() );
}

void LoopTest::closeTest()
{
	std::vector< Point3d > points;
	points.push_back( Point3d( 0.0, 0.0, 0.0 ) );
	points.push_back( Point3d( 1.0, 0.0, 0.0 ) );
	points.push_back( Point3d( 1.0, 1.0, 0.0 ) );
	Loop loop( points );
	BOOST_CHECK( loop.isOpen() );
	loop.close();
	BOOST_CHECK( loop.isClosed() );
}

void LoopTest::openTest()
{
	std::vector< Point3d > points;
	points.push_back( Point3d( 0.0, 0.0, 0.0 ) );
	points.push_back( Point3d( 1.0, 0.0, 0.0 ) );
	points.push_back( Point3d( 1.0, 1.0, 0.0 ) );
	points.push_back( Point3d( 0.0, 0.0, 0.0 ) );
	Loop loop( points );
	BOOST_CHECK( loop.isClosed() );
	loop.open();
	BOOST_CHECK( loop.isOpen() );
}