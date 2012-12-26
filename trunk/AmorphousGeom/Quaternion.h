#ifndef __QUATERNION_H__
#define __QUATERNION_H__

#include "Vector3d.h"
#include "Matrix3d.h"

namespace Amorphous{
	namespace Geom{

template <typename T = double>
class Quaternion
{
public:

	Quaternion(void) :x( 0.0), y( 0.0), z( 0.0), w( 1.0)
	{}

	Quaternion(const T x, const T y, const T z, const T w) : x( x), y( y), z( z), w( w)
	{}

	Quaternion(const Vector3d<T>& axis, const T angle) :
		x( axis.getX() * sin(angle * 0.5) ),
		y( axis.getY() * sin(angle * 0.5) ),
		z( axis.getZ() * sin(angle * 0.5) ),
		w( cos(angle * 0.5) )
	{}

	Matrix3d<T> getMatrix() const {
		const double x00 = ( 1.0 - 2.0 * y * y - 2.0 * z * z );
		const double x01 = ( 2.0 * x * y - 2.0 * z * w );
		const double x02 = ( 2.0 * x * z + 2.0 * y * w );

		const double x10 = ( 2.0 * x * y + 2.0 * z * w );
		const double x11 = ( 1.0 - 2.0 * x * x - 2.0 * z * z );
		const double x12 = ( 2.0 * y * z - 2.0 * x * w );
	
		const double x20 = ( 2.0 * x * z - 2.0 * y * w );
		const double x21 = ( 2.0 * y * z + 2.0 * x * w );
		const double x22 = ( 1.0 - 2.0 * x * x - 2.0 * y * y);

		return Matrix3d<T>( x00, x01, x02,
							x10, x11, x12,
							x20, x21, x22 );
	}

	Quaternion& operator+=( const Quaternion& rhs ) {
		x += rhs.getX();
		y += rhs.getY();
		z += rhs.getZ();
		w += rhs.getW();
		return *(this);
	}

	T getX() const { return x; }

	T getY() const { return y; }

	T getZ() const { return z; }

	T getW() const { return w; }

	T getNorm() const {
		return sqrt( pow( x, 2 ) + pow( y, 2 ) + pow( z, 2 ) + pow( w, 2 ) );
	}

	Quaternion& normalize() {
		const T norm = getNorm();
		x /= norm;
		y /= norm;
		z /= norm;
		z /= norm;
		assert( isNormalized() );
		return *this;
	}

	bool isNormalized() const {
		return Tolerances::isEqualAsDenominator( getNorm(), 1.0 );
	}

private:
	T x;
	T y;
	T z;
	T w;
};

	}
}

#endif