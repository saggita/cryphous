#ifndef __CRYSTAL_GEOMETRY_BOX_H__
#define __CRYSTAL_GEOMETRY_BOX_H__

#include <vector>

namespace Crystal{
	namespace Math{

class Vector3d;

class Box
{
public:
	
	Box::Box();

	Box::Box(const Vector3d& pointX, const Vector3d& pointY);

	Vector3d getCenter() const;
	
	float Box::getVolume() const;
	
	Vector3d Box::getMax() const;
	
	Vector3d Box::getMin() const;

	bool isInterior(const Vector3d &point) const;
	
	bool isExterior(const Vector3d &point) const;
	
	void outerOffset(const float offsetLength);
	
	Box getOuterOffset(const float offsetLength) const;

	void innerOffset(const float offsetLength);

	Box getInnerOffset(const float offsetLength) const;

	std::vector<Vector3d> createPoints( const float divideLength ) const;

	float getMaxX() const { return maxX; }

	float getMinX() const { return minX; }

	float getMaxY() const { return maxY; }

	float getMinY() const { return minY; }

	float getMaxZ() const { return maxZ; }

	float getMinZ() const { return minZ; }

private:
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