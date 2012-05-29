#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "Point3d.h"

namespace Crystal{
	namespace Geom{

class Sphere
{
public:

	Sphere();

	Sphere(const Point3d& center, const double radius);

	double getVolume() const;

	bool isInterior(const Point3d& point) const;

	bool isExterior(const Point3d& point) const;

	bool isDegenerated() const;

	double getRadius() const { return radius; }

	Point3d getCenter() const { return center; }

private:
	const Point3d center;
	const double radius;
};

	}
}

#endif