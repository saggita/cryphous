#include "TriangleTest.h"

#include "../CrystalGeom/Triangle.h"
#include "../CrystalGeom/Point3d.h"
#include "../CrystalGeom/Vector3d.h"
#include "../CrystalGeom/Line.h"

#include <boost/test/unit_test.hpp>

using namespace Crystal::Geom;

TriangleTest::TriangleTest(void)
{
	getPointsTest();
	getLinesTest();
	getNormalTest();
	getAreaTest();
}

void TriangleTest::getPointsTest()
{
	PointVector points;
	points.push_back( Point3d( 0.0, 0.0, 0.0 ) );
	points.push_back( Point3d( 1.0, 0.0, 0.0 ) );
	points.push_back( Point3d( 1.0, 1.0, 0.0 ) );
	
	Triangle triangle( points );
	PointVector results = triangle.getPoints();
	BOOST_CHECK( results.size() == 3 );
	for( int i = 0; i < 3; ++i ) {
		BOOST_CHECK( points[i] == results[i] );
	}
}

void TriangleTest::getLinesTest()
{
	PointVector points;
	points.push_back( Point3d( 0.0, 0.0, 0.0 ) );
	points.push_back( Point3d( 1.0, 0.0, 0.0 ) );
	points.push_back( Point3d( 1.0, 1.0, 0.0 ) );
	
	Triangle triangle( points );
	LineVector lines = triangle.getLines();
	BOOST_CHECK( lines.size() == 3 );
	BOOST_CHECK( lines[0] == Line( Point3d( 0.0, 0.0, 0.0), Point3d( 1.0, 0.0, 0.0 ) ) );
	BOOST_CHECK( lines[1] == Line( Point3d( 1.0, 0.0, 0.0), Point3d( 1.0, 1.0, 0.0 ) ) );
	BOOST_CHECK( lines[2] == Line( Point3d( 1.0, 1.0, 0.0), Point3d( 0.0, 0.0, 0.0 ) ) );
}

void TriangleTest::getNormalTest()
{
	PointVector points;
	points.push_back( Point3d( 0.0, 0.0, 0.0 ) );
	points.push_back( Point3d( 1.0, 0.0, 0.0 ) );
	points.push_back( Point3d( 1.0, 1.0, 0.0 ) );
	
	Triangle triangle( points );
	const Vector3d& normal = triangle.getNormal().normalize();
	BOOST_CHECK( normal == Vector3d( 0.0, 0.0, 1.0 ) );
}

void TriangleTest::getAreaTest()
{
	PointVector points;
	points.push_back( Point3d( 0.0, 0.0, 0.0 ) );
	points.push_back( Point3d( 1.0, 0.0, 0.0 ) );
	points.push_back( Point3d( 1.0, 1.0, 0.0 ) );
	
	Triangle triangle( points );
	const double area = triangle.getArea();
	BOOST_CHECK( area == 0.5 );
}
