#include "Box.h"

#include "Vector3d.h"

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

Box::Box(const Vector3d& pointX, const Vector3d& pointY) :
maxX( std::max( pointX.getX(), pointY.getX() ) ),
minX( std::min( pointX.getX(), pointY.getX() ) ),
maxY( std::max( pointX.getY(), pointY.getY() ) ),
minY( std::min( pointX.getY(), pointY.getY() ) ),
maxZ( std::max( pointX.getZ(), pointY.getZ() ) ),
minZ( std::min( pointX.getZ(), pointY.getZ() ) )
{
}

Vector3d Box::getCenter() const
{
	return Vector3d( (getMin() + getMax()).scale( 0.5 ) );
}

double Box::getVolume() const
{
	return (maxX - minX) * (maxY - minY) * (maxZ - minZ);
}

Vector3d Box::getMax() const
{
	return Vector3d( maxX, maxY, maxZ );
}

Vector3d Box::getMin() const
{
	return Vector3d( minX, minY, minZ );
}

bool Box::isInterior(const Vector3d &point) const
{
	const bool xIsInterior = ( minX < point.getX() && point.getX() < maxX );
	const bool yIsInterior = ( minY < point.getY() && point.getY() < maxY );
	const bool zIsInterior = ( minZ < point.getZ() && point.getZ() < maxZ );
	return xIsInterior && yIsInterior && zIsInterior;
}

bool Box::isExterior(const Vector3d &point) const
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