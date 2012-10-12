#ifndef __TRANSFORM_3D_H__
#define __TRANSFORM_3D_H__

#include "Vector3d.h"
#include "Matrix3d.h"

namespace Crystal{
	namespace Geom{

static Vector3d operator*(const Matrix3d lhs, const Vector3d &rhs)
{
	return Vector3d( 
		lhs.x00 * rhs.getX() + lhs.x01 * rhs.getY() + lhs.x02 * rhs.getZ(),
		lhs.x10 * rhs.getX() + lhs.x11 * rhs.getY() + lhs.x12 * rhs.getZ(),
		lhs.x20 * rhs.getX() + lhs.x21 * rhs.getY() + lhs.x22 * rhs.getZ() );
}

	}
}

#endif