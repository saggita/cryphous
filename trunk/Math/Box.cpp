#include "Box.h"

#include "Vector3d.h"

using namespace Crystal::Math;

Box::Box() :
	maxX( 1.0), minX( 0.0),
	maxY( 1.0), minY( 0.0),
	maxZ( 1.0), minZ( 0.0)
{}

Box::Box(const Vector3d& pointX, const Vector3d& pointY) :
	maxX( (pointX.getX() > pointY.getX() ) ? pointX.getX() : pointY.getX() ),
	minX( (pointX.getX() < pointY.getX() ) ? pointX.getX() : pointY.getX() ),
	maxY( (pointX.getY() > pointY.getY() ) ? pointX.getY() : pointY.getY() ),
	minY( (pointX.getY() < pointY.getY() ) ? pointX.getY() : pointY.getY() ),
	maxZ( (pointX.getZ() > pointY.getZ() ) ? pointX.getZ() : pointY.getZ() ),
	minZ( (pointX.getZ() < pointY.getZ() ) ? pointX.getZ() : pointY.getZ() )
{}

Vector3d Box::getCenter() const
{
	return Vector3d( (getMin() + getMax()).scale( 0.5 ) );
}
	
float Box::getVolume() const
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
	
void Box::outerOffset(const float offsetLength)
{
	minX -= offsetLength;
	minY -= offsetLength;
	minZ -= offsetLength;
	maxX += offsetLength;
	maxY += offsetLength;
	maxZ += offsetLength;
}
	
Box Box::getOuterOffset(const float offsetLength) const
{
	Box box = *this;
	box.outerOffset( offsetLength );
	return box;
}

void Box::innerOffset(const float offsetLength)
{
	outerOffset( -offsetLength );
}

Box Box::getInnerOffset(const float offsetLength) const
{
	return getOuterOffset( -offsetLength );
}

std::vector<Vector3d> Box::createPoints( const float divideLength ) const
{
	std::vector<Vector3d> points;
	for( float x = minX; x <= maxX; x+= divideLength ) {
		for( float y = minY; y <= maxY; y += divideLength ) {
			for( float z = minZ; z <= maxZ; z += divideLength ) {
				points.push_back( Vector3d( x, y, z ) );
			}
		}
	}
	return points;
}