#ifndef __BOX_H__
#define __BOX_H__

#include "Vector3d.h"

namespace Crystal{
	namespace Geom{

class Vector3d;
class Sphere;

class Box
{
public:
	
	Box::Box() :
	  maxX( 1.0), minX( 0.0), maxY( 1.0), minY( 0.0), maxZ( 1.0), minZ( 0.0)
	  {}

	Box::Box(const Vector3d& pointX, const Vector3d& pointY) :
	  maxX( (pointX.getX() > pointY.getX()) ? pointX.getX() : pointY.getX() ),
	  minX( (pointX.getX() < pointY.getX()) ? pointX.getX() : pointY.getX() ),
	  maxY( (pointX.getY() > pointY.getY()) ? pointX.getY() : pointY.getY() ),
	  minY( (pointX.getY() < pointY.getY()) ? pointX.getY() : pointY.getY() ),
	  maxZ( (pointX.getZ() > pointY.getZ()) ? pointX.getZ() : pointY.getZ() ),
	  minZ( (pointX.getZ() < pointY.getZ()) ? pointX.getZ() : pointY.getZ() )
	  {}

	Vector3d getCenter() const {
		return Vector3d( (getMin() + getMax()).scale( 0.5 ) );
	}
	
	float Box::getVolume() const {
		return (maxX - minX) * (maxY - minY) * (maxZ - minZ);
	}
	
	Vector3d Box::getMax() const {
		return Vector3d( maxX, maxY, maxZ );
	}
	
	Vector3d Box::getMin() const {
		return Vector3d( minX, minY, minZ );
	}

	float getMaxX() const { return maxX; }

	float getMinX() const { return minX; }

	float getMaxY() const { return maxY; }

	float getMinY() const { return minY; }

	float getMaxZ() const { return maxZ; }

	float getMinZ() const { return minZ; }

	bool isInterior(const Vector3d &point) const {
		const bool xIsInterior = ( minX < point.getX() && point.getX() < maxX );
		const bool yIsInterior = ( minY < point.getY() && point.getY() < maxY );
		const bool zIsInterior = ( minZ < point.getZ() && point.getZ() < maxZ );
		return xIsInterior && yIsInterior && zIsInterior;
	}
	
	bool isExterior(const Vector3d &point) const { return !isInterior(point); }
	
	void outerOffset(const float offsetLength) {
		minX -= offsetLength;
		minY -= offsetLength;
		minZ -= offsetLength;
		maxX += offsetLength;
		maxY += offsetLength;
		maxZ += offsetLength;
	}
	
	Box getOuterOffset(const float offsetLength) const {
		Box box = *this;
		box.outerOffset( offsetLength );
		return box;
	}

	void innerOffset(const float offsetLength) {
		outerOffset( -offsetLength );
	}

	Box getInnerOffset(const float offsetLength) const {
		return getOuterOffset( -offsetLength );
	}

public:
	float maxX;
	float minX;
	float maxY;
	float minY;
	float maxZ;
	float minZ;
};

	}
}

#endif