#ifndef __CRYSTAL_MATH_SPHERE_H__
#define __CRYSTAL_MATH_SPHERE_H__

#include "Vector3d.h"
#include "Box.h"

#include <vector>

namespace Crystal {
	namespace Math {

class Sphere
{
public:
	Sphere( Vector3d center, float radius ) :
	center( center ),
	radius( radius )
	{
	}

	std::vector<Vector3d> createPoints(const float divideLength ) const;

	Vector3d getCenter() const { return center; }

	float getRadius() const { return radius; }

private:
	Vector3d center;
	float radius;
};

	}
}

#endif