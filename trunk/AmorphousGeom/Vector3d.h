#ifndef __VECTOR_3D_H__
#define __VECTOR_3D_H__

#include "Matrix3d.h"

namespace Amorphous{
	namespace Geom{

template<typename T = double>
class Vector3d
{
public:
	
	Vector3d(void) :
	  x( 0.0 ), y( 0.0 ), z( 0.0 )
	  {
	  }

	Vector3d(T x, T y, T z) :
		x( x), y( y), z( z)
		{
		}

	Vector3d(const Vector3d& start, const Vector3d& end) :
		x( end.getX() - start.getX() ),
			y( end.getY() - start.getY() ),
			z( end.getZ() - start.getZ() )
		{}

	void setX(const T x){ this->x = x; }

	void setY(const T y){ this->y = y; }

	void setZ(const T z){ this->z = z; }

	T getX() const { return x; }

	T getY() const { return y; }

	T getZ() const { return z; }

	T getLengthSquared() const {
		return x*x + y*y + z*z;
	}

	T getLength() const {
		return ::sqrt( getLengthSquared() );
	}

	Vector3d scale(const T factor) {	
		x *= factor;
		y *= factor;
		z *= factor;
		return *this;
	}

	Vector3d getScaled(const T factor) const {
		return Vector3d( x * factor, y * factor, z * factor );
	}

	Vector3d normalize() {
		const T length = getLength();
		//assert( !Tolerances::isEqualAsDenominator( length ) );
		x /= length;
		y /= length;
		z /= length;
		//assert( isNormalized() );
		return *this;
	}

	Vector3d getNormalized() const {
		Vector3d vector = *(this);
		return vector.normalize();
	}

	bool isNormalized() const {
		return Tolerances::isEqualAsDistance( getLength(), 1.0 );
	}

	bool equals(const Vector3d& rhs) const {
		Vector3d diff( *this, rhs ); 
		return Tolerances::isEqualAsDistance( diff.getLength() );
	}

	bool isZero() const {
		return Tolerances::isEqualAsDistance( getLength() );
	}

	bool operator==(const Vector3d& rhs) const {
		return equals( rhs );
	}

	bool operator!=(const Vector3d& rhs) const {
		return !equals(rhs);
	}

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

	Vector3d operator*(const T factor) const {
		Vector3d vector( *this );
		return vector.scale( factor );
	}

	Vector3d Vector3d::operator/(const T factor) const {
		Vector3d vector( *this );
		return vector.scale( 1.0 / factor );
	}

	T getInnerProduct(const Vector3d& rhs) const {
		return x * rhs.getX() + y * rhs.getY() + z * rhs.getZ();
	}

	Vector3d getOuterProduct(const Vector3d& rhs) const {
		return Vector3d( y * rhs.getZ() - z * rhs.getY(),
			-( x * rhs.getZ() - z * rhs.getX() ),
			x * rhs.getY() - y * rhs.getX() );
	}
	
	Vector3d operator*=(const T factor) { return scale(factor); }

	Vector3d operator/=(const T factor) { return scale( 1.0 / factor); }

	Vector3d operator+(const Vector3d& rhs) const {
		return Vector3d( x + rhs.getX(), y + rhs.getY(), z + rhs.getZ() );
	}

	Vector3d operator-(const Vector3d& rhs) const {
		return Vector3d( x - rhs.getX(), y - rhs.getY(), z - rhs.getZ() );
	}

	/*void rotate(const Matrix3d& matrix) {
		*this = matrix.getMult( *this );
	}*/

	Vector3d getRotated(const Matrix3d<T>& matrix) const {
		Vector3d rotated( *this );
		rotated.rotate( matrix );
		return rotated;
	}

	Vector3d getMult(const Matrix3d<T>& matrix) const {
		return Vector3d( x * matrix.x00 + y * matrix.x10 + z * matrix.x20,
			x * matrix.x01 + y * matrix.x11 + z * matrix.x21,
			x * matrix.x02 + y * matrix.x12 + z * matrix.x22 );
	}

	const Vector3d operator*(const Matrix3d<T>& rhs) const {
		return getMult( rhs);
	}

	T getMaxElement() const {
		return std::max( std::max( x, y), z );
	}

	T getMinElement() const {
		return std::min( std::min( x, y), z );
	}

private:
	T x;
	T y;
	T z;
};

template<typename T>
static Vector3d<T> operator*(T factor, const Vector3d<T>& rhs) { return rhs.getScaled(factor); }

template<typename T>
static Vector3d<T> operator/(T factor, const Vector3d<T>& rhs) { return rhs.getScaled( 1.0 / factor ); }

template<typename T>
static Vector3d<T> operator*(const Matrix3d<T>& matrix, const Vector3d<T>& vector) {
	return Vector3d<T>( 
		matrix.x00 * vector.getX() + matrix.x01 * vector.getY() + matrix.x02 * vector.getZ(),
		matrix.x10 * vector.getX() + matrix.x11 * vector.getY() + matrix.x12 * vector.getZ(),
		matrix.x20 * vector.getX() + matrix.x21 * vector.getY() + matrix.x22 * vector.getZ()
		);
}

	}
}
#endif