#ifndef __VECTOR_2D_H__
#define __VECTOR_2D_H__

namespace Crystal{
	namespace Geom{

class Point2d;
class Matrix2d;

class Vector2d
{
public:
	
	Vector2d(void) :
	  x( 0.0 ), y( 0.0 )
	  {
	  }

	Vector2d(double x, double y) :
		x( x), y( y)
		{
		}

	Vector2d(const Point2d& start, const Point2d& end);

	Vector2d(const Vector2d& start, const Vector2d& end);

	Vector2d(const Point2d& point);

	void setX(const double x){ this->x = x; }

	void setY(const double y){ this->y = y; }

	double getX() const { return x; }

	double getY() const { return y; }

	double getLengthSquared() const {
		return x*x + y*y;
	}

	double getLength() const;

	Vector2d scale(const double factor) {	
		x *= factor;
		y *= factor;
		return *this;
	}

	Vector2d getScaled(const double factor) const {
		return Vector2d( x * factor, y * factor);
	}

	Vector2d normalize();

	Vector2d getNormalized() const;

	bool isNormalized() const;

	bool equals(const Vector2d& rhs) const;

	bool isZero() const;

	bool operator==(const Vector2d& rhs) const {
		return equals( rhs );
	}

	bool operator!=(const Vector2d& rhs) const {
		return !equals(rhs);
	}

	Vector2d operator+=(const Vector2d& rhs) {
		x += rhs.getX();
		y += rhs.getY();
		return *this;
	}

	Vector2d operator-=(const Vector2d& rhs) {
		x -= rhs.getX();
		y -= rhs.getY();
		return *this;
	}

	Vector2d operator*(const double factor) const {
		Vector2d vector( *this );
		return vector.scale( factor );
	}

	Vector2d operator/(const double factor) const {
		Vector2d vector( *this );
		return vector.scale( 1.0 / factor );
	}

	double getInnerProduct(const Vector2d& rhs) const {
		return x * rhs.getX() + y * rhs.getY();
	}
	
	void operator*=(const double factor) { scale(factor); }

	void operator/=(const double factor) { scale( 1.0 / factor); }

	Vector2d operator+(const Vector2d& rhs) const {
		return Vector2d( x + rhs.getX(), y + rhs.getY() );
	}

	Vector2d operator-(const Vector2d& rhs) const {
		return Vector2d( x - rhs.getX(), y - rhs.getY() );
	}

	Vector2d getMult(const Matrix2d& matrix) const;

	const Vector2d operator*(const Matrix2d& rhs) const;

private:
	double x;
	double y;
};

static Vector2d operator*(double factor, const Vector2d& rhs) { return rhs.getScaled(factor); }

static Vector2d operator/(double factor, const Vector2d& rhs) { return rhs.getScaled( 1.0 / factor ); }

	}
}

#endif