#include "Box.h"

#include "Point3d.h"

#include <algorithm>

using namespace Crystal::Geom;

Box::Box() :
maxX( 1.0),
minX( 0.0),
maxY( 1.0),
minY( 0.0),
maxZ( 1.0),
minZ( 0.0)
{
}

Box::Box(const Point3d& pointX, const Point3d& pointY) :
maxX( std::max( pointX.getX(), pointY.getX() ) ),
minX( std::min( pointX.getX(), pointY.getX() ) ),
maxY( std::max( pointX.getY(), pointY.getY() ) ),
minY( std::min( pointX.getY(), pointY.getY() ) ),
maxZ( std::max( pointX.getZ(), pointY.getZ() ) ),
minZ( std::min( pointX.getZ(), pointY.getZ() ) )
{
}

Point3d Box::getCenter() const
{
	return Point3d( (getMin() + getMax()).scale( 0.5 ) );
}

double Box::getVolume() const
{
	return (maxX - minX) * (maxY - minY) * (maxZ - minZ);
}

Point3d Box::getMax() const
{
	return Point3d( maxX, maxY, maxZ );
}

Point3d Box::getMin() const
{
	return Point3d( minX, minY, minZ );
}

bool Box::isInterior(const Point3d &point) const
{
	const bool xIsInterior = ( minX < point.getX() && point.getX() < maxX );
	const bool yIsInterior = ( minY < point.getY() && point.getY() < maxY );
	const bool zIsInterior = ( minZ < point.getZ() && point.getZ() < maxZ );
	return xIsInterior && yIsInterior && zIsInterior;
}

bool Box::isExterior(const Point3d &point) const
{
	return !isInterior(point);
}

void Box::outerOffset(const double offsetLength)
{
	minX -= offsetLength;
	minY -= offsetLength;
	minZ -= offsetLength;
	maxX += offsetLength;
	maxY += offsetLength;
	maxZ += offsetLength;
}

Box Box::getOuterOffset(const double offsetLength) const
{
	Box box = *this;
	box.outerOffset( offsetLength );
	return box;
}