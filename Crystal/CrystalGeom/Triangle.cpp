#include "Triangle.h"

#include "Point3d.h"
#include "Line.h"
#include "Vector3d.h"
#include "Loop.h"

#include <cassert>

using namespace Crystal::Geom;

Triangle::Triangle(const PointVector& points) :
points( points)
{
	assert( points.size() == 3 );
}

Triangle::Triangle(const Point3d& pointX, const Point3d& pointY, const Point3d& pointZ)
{
	points.push_back( pointX);
	points.push_back( pointY);
	points.push_back( pointZ);
	assert( points.size() == 3 );
}

LineVector Triangle::getLines() const
{
	Loop loop( points);
	loop.close();
	return loop.getLines();
}

Vector3d Triangle::getNormal() const
{
	const Vector3d vectorX = Vector3d(points[1]) - Vector3d(points[0]);
	const Vector3d vectorY = Vector3d(points[2]) - Vector3d(points[0]);
	return vectorX.getOuterProduct( vectorY );
}

double Triangle::getArea() const
{
	return getNormal().getLength() * 0.5;
}