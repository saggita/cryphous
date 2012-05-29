#ifndef __POINT_2D_H__
#define __POINT_2D_H__

#include "Vector2d.h"
#include <cmath>

namespace Crystal
{
	namespace Geom{
		class Matrix2d;

class Point2d
{
public:
	
	Point2d(void) :x(0.0),y(0.0)
	{
	}

	Point2d(double x, double y) : x( x), y( y)
	{
	}

	Point2d(const Vector2d& vector);

	void setX(double x){ this->x = x ;}

	void setY(double y){ this->y = y ;}

	double getX() const { return x; }

	double getY() const { return y; }

	double getDistanceSquared( const Point2d& rhs ) const{
		return std::pow( x - rhs.x, 2 ) + std::pow( y - rhs.y, 2 );
	}

	double getDistance(const Point2d& rhs) const {
		return std::sqrt( getDistanceSquared(rhs) );
	}

	bool equals (const Point2d& rhs) const;

	Point2d& scale( const double factor ) {
		x *= factor;
		y *= factor;
		return *this;
	}

	bool operator==( const Point2d& rhs) const {
		return equals( rhs );
	}

	bool operator!=( const Point2d& rhs) const {
		return !equals( rhs );
	}

	Point2d& operator+=( const Point2d& rhs ) {
		this->x += rhs.getX();
		this->y += rhs.getY();
		return *this;
	}

	Point2d& operator-=( const Point2d& rhs ) {
		this->x -= rhs.getX();
		this->y -= rhs.getY();
		return *this;
	}

	Point2d& operator*=( const double factor ) {
		this->scale( factor );
		return *this;
	}

	Point2d& operator/=( const double factor ) {
		this->scale( 1.0 / factor );
		return *this;
	}

	void rotate( const Matrix2d& matrix );

	Point2d getRotated( const Matrix2d& matrix ) const;

	Point2d move( const Vector2d& rhs ) { 
		this->x += rhs.getX();
		this->y += rhs.getY();
		return *this;
	}

	void addPertubation(const double xRange, const double yRange );

	Point2d getPertubated(const double xRange, const double yRange ) const;

private:
	double x;
	double y;
};

static Point2d operator*( const double factor, Point2d rhs ){ return rhs.scale( factor ); }

static Point2d operator+( Point2d lhs, const Vector2d& rhs ){ return lhs.move( rhs ); } 

	}
}

#endif