#ifndef __POINT_3D_H__
#define __POINT_3D_H__

#include "Vector3d.h"
#include <cmath>

namespace Crystal
{
	namespace Geom{
		class Matrix3d;

class Point3d
{
public:
	
	Point3d(void) :x(0.0),y(0.0),z(0.0)
	{
	}

	Point3d(double x, double y, double z) : x( x), y( y), z( z)
	{
	}

	Point3d(const Vector3d& vector);

	void setX(double x){ this->x = x ;}

	void setY(double y){ this->y = y ;}

	void setZ(double z){ this->z = z ;}

	double getX() const { return x; }

	double getY() const { return y; }

	double getZ() const { return z; }

	double getDistanceSquared( const Point3d& rhs ) const{
		return pow( x - rhs.x, 2 ) + pow( y - rhs.y, 2 ) + pow( z - rhs.z, 2 );
	}

	double getDistance(const Point3d& rhs) const {;
		return sqrt( getDistanceSquared(rhs) );
	}

	bool equals (const Point3d& rhs) const;

	Point3d& scale( const double factor ) {
		x *= factor;
		y *= factor;
		z *= factor;
		return *this;
	}

	bool operator==( const Point3d& rhs) const {
		return equals( rhs );
	}

	bool operator!=( const Point3d& rhs) const {
		return !equals( rhs );
	}

	Point3d& operator+=( const Point3d& rhs ) {
		this->x += rhs.getX();
		this->y += rhs.getY();
		this->z += rhs.getZ();
		return *this;
	}

	Point3d& Point3d::operator-=( const Point3d& rhs ) {
		this->x -= rhs.getX();
		this->y -= rhs.getY();
		this->z -= rhs.getZ();
		return *this;
	}

	Point3d& operator*=( const double factor ) {
		this->scale( factor );
		return *this;
	}

	Point3d& Point3d::operator/=( const double factor ) {
		this->scale( 1.0 / factor );
		return *this;
	}

	void rotate( const Matrix3d& matrix );

	Point3d getRotated( const Matrix3d& matrix ) const;

	Point3d move( const Vector3d& rhs ) { 
		this->x += rhs.getX();
		this->y += rhs.getY();
		this->z += rhs.getZ();
		return *this;
	}

	void addPertubation(const double xRange, const double yRange, const double zRange);

	Point3d getPertubated(const double xRange, const double yRange, const double zRange) const;

private:
	double x;
	double y;
	double z;
};

static Point3d operator*( const double factor, Point3d rhs ){ return rhs.scale( factor ); }

static Point3d operator+( Point3d lhs, const Vector3d& rhs ){ return lhs.move( rhs ); } 

	}
}

#endif