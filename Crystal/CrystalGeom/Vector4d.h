#ifndef __VECTOR_4D_H__
#define __VECTOR_4D_H__

namespace Crystal{
	namespace Geom{

class Point4d;
class Matrix4d;
class Vector3d;

class Vector4d
{
public:
	
	Vector4d(void) :
	  x( 0.0 ), y( 0.0 ), z( 0.0 ), w(0.0)
	  {
	  }

	Vector4d(double x, double y, double z, double w) :
		x( x), y( y), z( z), w( w)
		{
		}

	Vector4d(const Point4d& start, const Point4d& end);

	Vector4d(const Vector4d& start, const Vector4d& end);

	Vector4d(const Point4d& point);

	void setX(const double x){ this->x = x; }

	void setY(const double y){ this->y = y; }

	void setZ(const double z){ this->z = z; }

	void setW(const double w){ this->w = w; }

	double getX() const { return x; }

	double getY() const { return y; }

	double getZ() const { return z; }

	double getW() const { return w; }

	double getLengthSquared() const {
		return x*x + y*y + z*z + w*w;
	}

	double getLength() const;

	Vector4d scale(const double factor) {	
		x *= factor;
		y *= factor;
		z *= factor;
		w *= factor;
		return *this;
	}

	Vector4d getScaled(const double factor) const {
		return Vector4d( x * factor, y * factor, z * factor, w * factor );
	}

	Vector4d normalize();

	Vector4d getNormalized() const;

	bool isNormalized() const;

	bool equals(const Vector4d& rhs) const;

	bool isZero() const;

	bool operator==(const Vector4d& rhs) const {
		return equals( rhs );
	}

	bool operator!=(const Vector4d& rhs) const {
		return !equals(rhs);
	}

	Vector4d operator+=(const Vector4d& rhs) {
		x += rhs.getX();
		y += rhs.getY();
		z += rhs.getZ();
		w += rhs.getW();
		return *this;
	}

	Vector4d operator-=(const Vector4d& rhs) {
		x -= rhs.getX();
		y -= rhs.getY();
		z -= rhs.getZ();
		w -= rhs.getW();
		return *this;
	}

	Vector4d operator*(const double factor) const {
		Vector4d vector( *this );
		return vector.scale( factor );
	}

	Vector4d Vector4d::operator/(const double factor) const {
		Vector4d vector( *this );
		return vector.scale( 1.0 / factor );
	}

	double getInnerProduct(const Vector4d& rhs) const {
		return x * rhs.getX() + y * rhs.getY() + z * rhs.getZ() + w * rhs.getW();
	}
	
	void operator*=(const double factor) { scale(factor); }

	void operator/=(const double factor) { scale( 1.0 / factor); }

	Vector4d operator+(const Vector4d& rhs) const {
		return Vector4d( x + rhs.getX(), y + rhs.getY(), z + rhs.getZ(), w + rhs.getW() );
	}

	Vector4d operator-(const Vector4d& rhs) const {
		return Vector4d( x - rhs.getX(), y - rhs.getY(), z - rhs.getZ(), w - rhs.getW() );
	}

	void rotate(const Matrix4d& matrix);

	Vector4d getRotated(const Matrix4d& matrix) const {
		Vector4d rotated( *this );
		rotated.rotate( matrix );
		return rotated;
	}

	Vector3d getVector3d() const;

private:
	double x;
	double y;
	double z;
	double w;
};

static Vector4d operator*(double factor, const Vector4d& rhs) { return rhs.getScaled(factor); }

static Vector4d operator/(double factor, const Vector4d& rhs) { return rhs.getScaled( 1.0 / factor ); }

	}
}

#endif