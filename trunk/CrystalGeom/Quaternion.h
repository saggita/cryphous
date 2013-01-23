#ifndef __QUATERNION_H__
#define __QUATERNION_H__

#include "Vector3d.h"

namespace Crystal{
	namespace Geom{


class Matrix3d;

class Quaternion
{
public:
	
	Quaternion(void) : x( 0.0), y( 0.0), z( 0.0), w( 1.0) 
	{}
	
	Quaternion::Quaternion(const float x, const float y, const float z, const float w) : x( x), y( y), z( z), w( w)
	{}
	
	Quaternion::Quaternion(const Vector3d& axis, const float angle) :
	x( axis.x * sin(angle * 0.5f) ), 
		y( axis.y * sin(angle * 0.5f) ), 
		z( axis.z * sin(angle * 0.5f) ), 
		w( cos(angle * 0.5f) )
	{
		assert( axis.isNormalized() );
	}

	Matrix3d getMatrix() const {
		const float x00 = ( 1.0f - 2.0f * y * y - 2.0f * z * z );
		const float x01 = ( 2.0f * x * y - 2.0f * z * w );
		const float x02 = ( 2.0f * x * z + 2.0f * y * w );

		const float x10 = ( 2.0f * x * y + 2.0f * z * w );
		const float x11 = ( 1.0f - 2.0f * x * x - 2.0f * z * z );
		const float x12 = ( 2.0f * y * z - 2.0f * x * w );
	
		const float x20 = ( 2.0f * x * z - 2.0f * y * w );
		const float x21 = ( 2.0f * y * z + 2.0f * x * w );
		const float x22 = ( 1.0f - 2.0f * x * x - 2.0f * y * y);

		return Matrix3d( x00, x01, x02,
							x10, x11, x12,
							x20, x21, x22 );
	}
	
	Quaternion& operator+=( const Quaternion& rhs )
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		w += rhs.getW();
		return *(this);
	}

	float getX() const { return x; }

	float getY() const { return y; }

	float getZ() const { return z; }

	float getW() const { return w; }

	float getNorm() const {
		return sqrt( pow( x, 2 ) + pow( y, 2 ) + pow( z, 2 ) + pow( w, 2 ) );
	}

	Quaternion& normalize()
	{
		const float norm = getNorm();
		x /= norm;
		y /= norm;
		z /= norm;
		z /= norm;
		assert( isNormalized() );
		return *this;
	}

	bool isNormalized() const { return Tolerances::isEqualStrictly( getNorm(), 1.0 ); }

private:
	float x;
	float y;
	float z;
	float w;
};

	}
}

#endif