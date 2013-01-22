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
	  maxX( (pointX.x > pointY.x) ? pointX.x : pointY.x ),
	  minX( (pointX.x < pointY.x) ? pointX.x : pointY.x ),
	  maxY( (pointX.y > pointY.y) ? pointX.y : pointY.y ),
	  minY( (pointX.y < pointY.y) ? pointX.y : pointY.y ),
	  maxZ( (pointX.z > pointY.z) ? pointX.z : pointY.z ),
	  minZ( (pointX.z < pointY.z) ? pointX.z : pointY.z )
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
		const bool xIsInterior = ( minX < point.x && point.x < maxX );
		const bool yIsInterior = ( minY < point.y && point.y < maxY );
		const bool zIsInterior = ( minZ < point.z && point.z < maxZ );
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