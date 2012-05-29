#include "Square.h"

#include <cassert>

using namespace Crystal::Geom;

Square::Square(const Point3d& center, const double length) :
center( center),
length( length)
{
}

Square::~Square(void)
{
}

std::vector<Point3d> Square::getPoints() const
{
	const double halfLength = length * 0.5;
	std::vector<Point3d> points;
	points.push_back( Point3d( center.getX() - halfLength, center.getY() + halfLength, 0.0 ) );
	points.push_back( Point3d( center.getX() - halfLength, center.getY() - halfLength, 0.0 ) );
	points.push_back( Point3d( center.getX() + halfLength, center.getY() - halfLength, 0.0 ) );
	points.push_back( Point3d( center.getX() + halfLength, center.getY() + halfLength, 0.0 ) );
	return points;
}

std::vector<Point3d> Square::getInnerPoints(const double divideLength) const
{
	std::vector<Point3d> points;
	//const Vector3d vectorX( points[0], points[1] );
	//const int xDivide = static_cast<int>( vectorX.getLength() / vectorX.getLength() );
	//for(int i = 0; i < xDivide; ++i ) {
	//	xDivide
	//}
	assert( false );
	return points;
}