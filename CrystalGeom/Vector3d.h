#ifndef __VECTOR_3D_H__
#define __VECTOR_3D_H__

#include <cassert>
#include <cmath>
#include "Matrix3d.h"
#include "Tolerances.h"

namespace Crystal{
	namespace Geom{

class Vector3d
{
public:
	
	Vector3d(void) :
	  x( 0.0 ), y( 0.0 ), z( 0.0 )
	  {
	  }

	Vector3d(float x, float y, float z) :
		x( x), y( y), z( z)
		{
		}

	Vector3d(const Vector3d& start, const Vector3d& end) :
		x( end.getX() - start.getX() ),
			y( end.getY() - start.getY() ),
			z( end.getZ() - start.getZ() )
		{
		}

	void setX(const float x){ this->x = x; }

	void setY(const float y){ this->y = y; }

	void setZ(const float z){ this->z = z; }

	float getX() const { return x; }

	float getY() const { return y; }

	float getZ() const { return z; }

	float getLengthSquared() const {
		return x*x + y*y + z*z;
	}

	float getLength() const {
		return ::sqrt( getLengthSquared() );
	}

	float getDistance(const Vector3d& rhs) const {;
		return sqrt( getDistanceSquared(rhs) );
	}

	float getDistanceSquared( const Vector3d& rhs ) const{
		return pow( x - rhs.x, 2 ) + pow( y - rhs.y, 2 ) + pow( z - rhs.z, 2 );
	}

	Vector3d scale(const float factor) {	
		x *= factor;
		y *= factor;
		z *= factor;
		return *this;
	}

	Vector3d getScaled(const float factor) const {
		return Vector3d( x * factor, y * factor, z * factor );
	}

	Vector3d normalize() {
		const float length = getLength();
		x /= length;
		y /= length;
		z /= length;
		return *this;
	}

	Vector3d Vector3d::getNormalized() const {
		Vector3d vector = *(this);
		return vector.normalize();
	}

	bool isNormalized() const { return Tolerances::isEqualAsDistance( getLength(), 1.0 ); }

	bool equals(const Vector3d &rhs) const { return Tolerances::isEqualAsDistance( getDistance( rhs ) ); }

	bool isZero() const { return Tolerances::isEqualAsDistance( getLength() ); }

	bool operator==(const Vector3d& rhs) const { return equals( rhs ); }

	bool operator!=(const Vector3d& rhs) const { return !equals(rhs); }

	Vector3d operator+=(const Vector3d& rhs) {
		x += rhs.getX();
		y += rhs.getY();
		z += rhs.getZ();
		return *this;
	}

	Vector3d operator-=(const Vector3d& rhs) {
		x -= rhs.getX();
		y -= rhs.getY();
		z -= rhs.getZ();
		return *this;
	}

	Vector3d operator*(const float factor) const {
		Vector3d vector( *this );
		return vector.scale( factor );
	}

	Vector3d Vector3d::operator/(const float factor) const {
		Vector3d vector( *this );
		return vector.scale( 1.0f / factor );
	}

	float getInnerProduct(const Vector3d& rhs) const {
		return x * rhs.getX() + y * rhs.getY() + z * rhs.getZ();
	}

	Vector3d getOuterProduct(const Vector3d& rhs) const {
		return Vector3d( y * rhs.getZ() - z * rhs.getY(),
			-( x * rhs.getZ() - z * rhs.getX() ),
			x * rhs.getY() - y * rhs.getX() );
	}
	
	Vector3d operator*=(const float factor) { return scale(factor); }

	Vector3d operator/=(const float factor) { return scale( 1.0f / factor); }

	Vector3d operator+(const Vector3d& rhs) const {
		return Vector3d( x + rhs.getX(), y + rhs.getY(), z + rhs.getZ() );
	}

	Vector3d operator-(const Vector3d& rhs) const {
		return Vector3d( x - rhs.getX(), y - rhs.getY(), z - rhs.getZ() );
	}

	void rotate(const Matrix3d& matrix) {
		*(this) = getRotated( matrix );
	}

	Vector3d getRotated(const Matrix3d& matrix) const {
		return Vector3d( 
			matrix.x00 * x + matrix.x01 * y + matrix.x02 * z,
			matrix.x10 * x + matrix.x11 * y + matrix.x12 * z,
			matrix.x20 * x + matrix.x21 * y + matrix.x22 * z
			);
	}

	Vector3d getMult(const Matrix3d& matrix) const {
		return Vector3d( x * matrix.x00 + y * matrix.x10 + z * matrix.x20,
			x * matrix.x01 + y * matrix.x11 + z * matrix.x21,
			x * matrix.x02 + y * matrix.x12 + z * matrix.x22 );
	}
	
	const Vector3d Vector3d::operator*(const Matrix3d& rhs) const { return getMult( rhs); }

private:
	float x;
	float y;
	float z;
};

static Vector3d operator*(float factor, const Vector3d& rhs) { return rhs.getScaled(factor); }

static Vector3d operator/(float factor, const Vector3d& rhs) { return rhs.getScaled( 1.0f / factor ); }

	}
}

#endif