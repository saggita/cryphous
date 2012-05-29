#ifndef __VECTOR_3D_H__
#define __VECTOR_3D_H__

namespace Crystal{
	namespace Geom{

class Point3d;
class Matrix3d;

class Vector3d
{
public:
	
	Vector3d(void) :
	  x( 0.0 ), y( 0.0 ), z( 0.0 )
	  {
	  }

	Vector3d(double x, double y, double z) :
		x( x), y( y), z( z)
		{
		}

	Vector3d(const Point3d& start, const Point3d& end);

	Vector3d(const Vector3d& start, const Vector3d& end);

	Vector3d(const Point3d& point);

	void setX(const double x){ this->x = x; }

	void setY(const double y){ this->y = y; }

	void setZ(const double z){ this->z = z; }

	double getX() const { return x; }

	double getY() const { return y; }

	double getZ() const { return z; }

	double getLengthSquared() const {
		return x*x + y*y + z*z;
	}

	double getLength() const;

	Vector3d scale(const double factor) {	
		x *= factor;
		y *= factor;
		z *= factor;
		return *this;
	}

	Vector3d getScaled(const double factor) const {
		return Vector3d( x * factor, y * factor, z * factor );
	}

	Vector3d normalize();

	Vector3d getNormalized() const;

	bool isNormalized() const;

	bool equals(const Vector3d& rhs) const;

	bool isZero() const;

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

	Vector3d operator*(const double factor) const {
		Vector3d vector( *this );
		return vector.scale( factor );
	}

	Vector3d Vector3d::operator/(const double factor) const {
		Vector3d vector( *this );
		return vector.scale( 1.0 / factor );
	}

	double getInnerProduct(const Vector3d& rhs) const {
		return x * rhs.getX() + y * rhs.getY() + z * rhs.getZ();
	}

	Vector3d getOuterProduct(const Vector3d& rhs) const {
		return Vector3d( y * rhs.getZ() - z * rhs.getY(),
			-( x * rhs.getZ() - z * rhs.getX() ),
			x * rhs.getY() - y * rhs.getX() );
	}
	
	void operator*=(const double factor) { scale(factor); }

	void operator/=(const double factor) { scale( 1.0 / factor); }

	Vector3d operator+(const Vector3d& rhs) const {
		return Vector3d( x + rhs.getX(), y + rhs.getY(), z + rhs.getZ() );
	}

	Vector3d operator-(const Vector3d& rhs) const {
		return Vector3d( x - rhs.getX(), y - rhs.getY(), z - rhs.getZ() );
	}

	void rotate(const Matrix3d& matrix);

	Vector3d getRotated(const Matrix3d& matrix) const {
		Vector3d rotated( *this );
		rotated.rotate( matrix );
		return rotated;
	}

	Vector3d getMult(const Matrix3d& matrix) const;

	const Vector3d operator*(const Matrix3d& rhs) const;

	double getMaxElement() const;

	double getMinElement() const;

private:
	double x;
	double y;
	double z;
};

static Vector3d operator*(double factor, const Vector3d& rhs) { return rhs.getScaled(factor); }

static Vector3d operator/(double factor, const Vector3d& rhs) { return rhs.getScaled( 1.0 / factor ); }

	}
}

#endif