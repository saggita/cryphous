#ifndef __POINT_4D_H__
#define __POINT_4D_H__

#include "Vector4d.h"
#include <cmath>

namespace Crystal
{
	namespace Geom{
		class Matrix4d;
		class Point3d;

class Point4d
{
public:
	
	Point4d(void) :x(0.0),y(0.0),z(0.0),w(0.0)
	{
	}

	Point4d(double x, double y, double z, double w) : x( x), y( y), z( z), w( w)
	{
	}

	Point4d(const Vector4d& vector);

	void setX(double x){ this->x = x ;}

	void setY(double y){ this->y = y ;}

	void setZ(double z){ this->z = z ;}

	void setW(double w){ this->w = w ;}

	double getX() const { return x; }

	double getY() const { return y; }

	double getZ() const { return z; }

	double getW() const { return w; }

	double getDistanceSquared( const Point4d& rhs ) const{
		return pow( x - rhs.x, 2 ) + pow( y - rhs.y, 2 ) + pow( z - rhs.z, 2 ) + pow( w - rhs.w, 2 );
	}

	double getDistance(const Point4d& rhs) const {
		return sqrt( getDistanceSquared(rhs) );
	}

	bool equals (const Point4d& rhs) const;

	Point4d& scale( const double factor ) {
		x *= factor;
		y *= factor;
		z *= factor;
		w *= factor;
		return *this;
	}

	bool operator==( const Point4d& rhs) const {
		return equals( rhs );
	}

	bool operator!=( const Point4d& rhs) const {
		return !equals( rhs );
	}

	Point4d& operator+=( const Point4d& rhs ) {
		this->x += rhs.getX();
		this->y += rhs.getY();
		this->z += rhs.getZ();
		this->w += rhs.getW();
		return *this;
	}

	Point4d& Point4d::operator-=( const Point4d& rhs ) {
		this->x -= rhs.getX();
		this->y -= rhs.getY();
		this->z -= rhs.getZ();
		this->w -= rhs.getW();
		return *this;
	}

	Point4d& operator*=( const double factor ) {
		this->scale( factor );
		return *this;
	}

	Point4d& Point4d::operator/=( const double factor ) {
		this->scale( 1.0 / factor );
		return *this;
	}

	void rotate( const Matrix4d& matrix );

	Point4d getRotated( const Matrix4d& matrix ) const;

	Point4d move( const Vector4d& rhs ) { 
		this->x += rhs.getX();
		this->y += rhs.getY();
		this->z += rhs.getZ();
		this->w += rhs.getW();
		return *this;
	}

	Point3d getPoint3d() const;

private:
	double x;
	double y;
	double z;
	double w;
};

static Point4d operator*( const double factor, Point4d rhs ){ return rhs.scale( factor ); }

static Point4d operator+( Point4d lhs, const Vector4d& rhs ){ return lhs.move( rhs ); } 

	}
}

#endif