#ifndef __BOX_H__
#define __BOX_H__

namespace Crystal{
	namespace Geom{

class Vector3d;
class Sphere;

class Box
{
public:

	Box();

	Box(const Vector3d& pointX, const Vector3d& pointY);

	double getVolume() const;

	Vector3d getMax() const;

	Vector3d getMin() const;

	Vector3d getCenter() const;

	double getMaxX() const { return maxX; }

	double getMinX() const { return minX; }

	double getMaxY() const { return maxY; }

	double getMinY() const { return minY; }

	double getMaxZ() const { return maxZ; }

	double getMinZ() const { return minZ; }

	bool isInterior(const Vector3d& point) const;

	bool isExterior(const Vector3d& point) const;

	void outerOffset(const double offsetLength);

	Box getOuterOffset(const double offsetLength) const;

	void innerOffset(const double offsetLength) {
		outerOffset( -offsetLength );
	}

	Box getInnerOffset(const double offsetLength) const {
		return getOuterOffset( -offsetLength );
	}

private:
	double maxX;
	double minX;
	double maxY;
	double minY;
	double maxZ;
	double minZ;
};

	}
}

#endif