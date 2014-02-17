#ifndef __CRSYTAL_GEOMETRY_VECTOR_3D_H__
#define __CRSYTAL_GEOMETRY_VECTOR_3D_H__

#include <cmath>
#include "Tolerances.h"

namespace Crystal{
	namespace Math{

class Matrix3d;

class Vector3d
{
public:
	
	Vector3d( void );

	Vector3d( float x, float y, float z );

	Vector3d( const Vector3d& start, const Vector3d& end );

	static Vector3d Zero() { return Vector3d( 0.0f, 0.0f, 0.0f ); }

	static Vector3d UnitX() { return Vector3d( 1.0f, 0.0f, 0.0f ); }

	static Vector3d UnitY() { return Vector3d( 0.0f, 1.0f, 0.0f ); }

	static Vector3d UnitZ() { return Vector3d( 0.0f, 0.0f, 1.0f ); }

	void setZero();

	float getLengthSquared() const;

	float getLength() const;
	
	float getDistance( const Vector3d& rhs ) const;

	float getDistanceSquared( const Vector3d& rhs ) const;

	Vector3d scale( const float factor );

	Vector3d getScaled( const float factor ) const;

	Vector3d normalize();

	Vector3d getNormalized() const;

	bool isNormalized() const;

	bool equals( const Vector3d &rhs ) const;

	bool isZero() const;

	bool operator==( const Vector3d& rhs ) const;

	bool operator!=(const Vector3d& rhs) const;

	Vector3d operator+(const Vector3d& rhs) const;

	Vector3d operator-(const Vector3d& rhs) const;

	Vector3d operator+=(const Vector3d& rhs);

	Vector3d operator-=(const Vector3d& rhs);

	Vector3d operator*(const float factor) const;

	Vector3d operator/(const float factor) const;

	float getInnerProduct(const Vector3d& rhs) const {
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}

	Vector3d getOuterProduct(const Vector3d& rhs) const {
		return Vector3d( y * rhs.z - z * rhs.y,
			-( x * rhs.z - z * rhs.x ),
			x * rhs.y - y * rhs.x );
	}
	
	Vector3d operator*=( const float factor ) { return scale( factor ); }

	Vector3d operator/=( const float factor ) { return scale( 1.0f / factor ); }

	void rotate(const Matrix3d& matrix);

	Vector3d getRotated(const Matrix3d& matrix) const;

	Vector3d getMult(const Matrix3d& matrix) const;
	
	const Vector3d Vector3d::operator*( const Matrix3d& rhs ) const;

public:
	float getX() const { return x; }

	float getY() const { return y; }

	float getZ() const { return z; }

private:
	float x;
	float y;
	float z;
};

static Vector3d operator*( float factor, const Vector3d& rhs ) { return rhs.getScaled( factor ); }

static Vector3d operator/( float factor, const Vector3d& rhs ) { return rhs.getScaled( 1.0f / factor ); }

	}
}

#endif