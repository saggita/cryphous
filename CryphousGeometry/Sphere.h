#ifndef __CRYPHOUS_SPHERE_H__
#define __CRYPHOUS_SPHERE_H__

#include "Tolerances.h"
#include "Vector3d.h"

namespace Cryphous{
	namespace Geometry{

class Sphere
{
public:
	
	Sphere() :
	  center( Vector3d( 0.0, 0.0, 0.0) ),
	  radius( 1.0f )
	  {}

	Sphere(const Vector3d& center, const float radius) :
		center( center),
		radius( radius)
	  {}
	
	float getVolume() const {
		return (radius * radius * radius * Tolerances::getPI() * 4.0) / 3.0;	}

	bool isInterior(const Vector3d &point) const {
		return point.getDistanceSquared( center ) < (radius * radius);
	}
	
	bool isExterior(const Vector3d &point) const { return !isInterior(point); }
	
	void outerOffset(const float offsetLength) {
		radius += offsetLength;
	}
	
	Sphere getOuterOffset(const float offsetLength) const {
		Sphere sphere = *this;
		sphere.outerOffset( offsetLength );
		return sphere;
	}

	void innerOffset(const float offsetLength) {
		outerOffset( -offsetLength );
	}

	Sphere getInnerOffset(const float offsetLength) const {
		return getOuterOffset( -offsetLength );
	}

public:
	Vector3d center;
	float radius;
};

	}
}

#endif