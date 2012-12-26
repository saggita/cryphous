#ifndef __BOX_H__
#define __BOX_H__

#include "Vector3d.h"

namespace Amorphous{
	namespace Geom{

template<typename T = double>
class Box
{
public:

	Box() :
	  maxX( 1.0),minX( 0.0),maxY( 1.0),minY( 0.0),maxZ( 1.0),minZ( 0.0)
	  {}

	Box(const Vector3d<>& pointX, const Vector3d<>& pointY) :
		maxX( std::max( pointX.getX(), pointY.getX() ) ),
		minX( std::min( pointX.getX(), pointY.getX() ) ),
		maxY( std::max( pointX.getY(), pointY.getY() ) ),
		minY( std::min( pointX.getY(), pointY.getY() ) ),
		maxZ( std::max( pointX.getZ(), pointY.getZ() ) ),
		minZ( std::min( pointX.getZ(), pointY.getZ() ) )
		{}

	T getVolume() const {
		return (maxX - minX) * (maxY - minY) * (maxZ - minZ);
	}

	Vector3d<T> getMax() const {
		return Vector3d<T>( maxX, maxY, maxZ );
	}

	Vector3d<T> getMin() const {
		return Vector3d<T>( minX, minY, minZ );
	}

	Vector3d<T> getCenter() const {
		return Vector3d<T>( (getMin() + getMax()).scale( 0.5 ) );
	}

	T getMaxX() const { return maxX; }

	T getMinX() const { return minX; }

	T getMaxY() const { return maxY; }

	T getMinY() const { return minY; }

	T getMaxZ() const { return maxZ; }

	T getMinZ() const { return minZ; }

	bool isInterior(const Vector3d<>& point) const {
		const bool xIsInterior = ( minX < point.getX() && point.getX() < maxX );
		const bool yIsInterior = ( minY < point.getY() && point.getY() < maxY );
		const bool zIsInterior = ( minZ < point.getZ() && point.getZ() < maxZ );
		return xIsInterior && yIsInterior && zIsInterior;
	}

	bool isExterior(const Vector3d<>& point) const {
		return !isInterior(point);
	}

	void outerOffset(const T offsetLength) {
		minX -= offsetLength;
		minY -= offsetLength;
		minZ -= offsetLength;
		maxX += offsetLength;
		maxY += offsetLength;
		maxZ += offsetLength;
	}

	Box getOuterOffset(const T offsetLength) const {
		Box box = *this;
		box.outerOffset( offsetLength );
		return box;
	}

	void innerOffset(const T offsetLength) {
		outerOffset( -offsetLength );
	}

	Box getInnerOffset(const T offsetLength) const {
		return getOuterOffset( -offsetLength );
	}

private:
	T maxX;
	T minX;
	T maxY;
	T minY;
	T maxZ;
	T minZ;
};

	}
}

#endif