#include "Sphere.h"

#include "Tolerances.h"

#include <cmath>

using namespace Crystal::Geom;

Sphere::Sphere(void) :
center( 0.0, 0.0, 0.0),
radius( 0.0)
{
}

Sphere::Sphere(const Crystal::Geom::Point3d &center, const double radius) :
center( center),
radius( radius)
{
}

double Sphere::getVolume() const
{
	return 4.0 / 3.0 * Tolerances::getPI() * std::pow( radius, 3 );
}

bool Sphere::isDegenerated() const
{
	return Tolerances::isEqualAsDenominator( getVolume() );
}

bool Sphere::isExterior(const Point3d& point) const
{
	return center.getDistanceSquared( point ) > radius;
}

bool Sphere::isInterior(const Point3d& point) const
{
	return !isExterior(point);
}