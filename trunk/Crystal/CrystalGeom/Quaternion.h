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
	
	Quaternion::Quaternion(const double x, const double y, const double z, const double w) : x( x), y( y), z( z), w( w)
	{}
	
	Quaternion::Quaternion(const Vector3d& axis, const double angle) :
	x( axis.getX() * sin(angle * 0.5) ), 
		y( axis.getY() * sin(angle * 0.5) ), 
		z( axis.getZ() * sin(angle * 0.5) ), 
		w( cos(angle * 0.5) )
	{
		assert( axis.isNormalized() );
	}

	Matrix3d getMatrix() const {
		const double x00 = ( 1.0 - 2.0 * y * y - 2.0 * z * z );
		const double x01 = ( 2.0 * x * y - 2.0 * z * w );
		const double x02 = ( 2.0 * x * z + 2.0 * y * w );

		const double x10 = ( 2.0 * x * y + 2.0 * z * w );
		const double x11 = ( 1.0 - 2.0 * x * x - 2.0 * z * z );
		const double x12 = ( 2.0 * y * z - 2.0 * x * w );
	
		const double x20 = ( 2.0 * x * z - 2.0 * y * w );
		const double x21 = ( 2.0 * y * z + 2.0 * x * w );
		const double x22 = ( 1.0 - 2.0 * x * x - 2.0 * y * y);

		return Matrix3d( x00, x01, x02,
							x10, x11, x12,
							x20, x21, x22 );
	}
	
	Quaternion& operator+=( const Quaternion& rhs )
	{
		x += rhs.getX();
		y += rhs.getY();
		z += rhs.getZ();
		w += rhs.getW();
		return *(this);
	}

	double getX() const { return x; }

	double getY() const { return y; }

	double getZ() const { return z; }

	double getW() const { return w; }

	double getNorm() const {
		return sqrt( pow( x, 2 ) + pow( y, 2 ) + pow( z, 2 ) + pow( w, 2 ) );
	}

	Quaternion& normalize()
	{
		const double norm = getNorm();
		x /= norm;
		y /= norm;
		z /= norm;
		z /= norm;
		assert( isNormalized() );
		return *this;
	}

	bool isNormalized() const { return Tolerances::isEqualAsDenominator( getNorm(), 1.0 ); }

private:
	double x;
	double y;
	double z;
	double w;
};

	}
}

#endif