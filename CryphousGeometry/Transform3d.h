#ifndef __TRANSFORM_3D_H__
#define __TRANSFORM_3D_H__

#include "Vector3d.h"
#include "Matrix3d.h"

namespace Crystal{
	namespace Geom{

static Vector3d operator*(const Matrix3d lhs, const Vector3d &rhs)
{
	return Vector3d( 
		lhs.x00 * rhs.x + lhs.x01 * rhs.y + lhs.x02 * rhs.z,
		lhs.x10 * rhs.x + lhs.x11 * rhs.y + lhs.x12 * rhs.z,
		lhs.x20 * rhs.x + lhs.x21 * rhs.y + lhs.x22 * rhs.z );
}

	}
}

#endif