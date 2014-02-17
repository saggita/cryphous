#ifndef __CRYSTAL_GEOMETRY_QUATERNION_H__
#define __CRYSTAL_GEOMETRY_QUATERNION_H__

#include "Vector3d.h"

namespace Crystal{
	namespace Math{


class Matrix3d;

class Quaternion
{
public:
	
	Quaternion(void);
	
	Quaternion(const float x, const float y, const float z, const float w);
	
	Quaternion(const Vector3d& axis, const float angle);

	Matrix3d getMatrix() const;
	
	Quaternion& operator+=( const Quaternion& rhs );

	float getNorm() const;

	Quaternion& normalize();

	bool isNormalized() const;

private:
	float x;
	float y;
	float z;
	float w;
};

	}
}

#endif