#include "Point2d.h"
#include "Tolerances.h"
#include "Vector2d.h"
#include "Matrix2d.h"

#include <cmath>
#include <cassert>
#include <cstdlib>

using namespace Crystal::Geom;

Point2d::Point2d(const Vector2d& vector) :
x( vector.getX() ),
y( vector.getY() )
{
}

bool Point2d::equals(const Point2d& rhs) const
{
	return Tolerances::isEqualAsDistance( getDistance( rhs ) );
}

void Point2d::rotate( const Matrix2d& matrix )
{
	*(this) = getRotated( matrix );
}

Point2d Point2d::getRotated( const Matrix2d& matrix ) const
{
	return Point2d( 
		matrix.x00 * x + matrix.x01 * y,
		matrix.x10 * x + matrix.x11 * y );
}

void Point2d::addPertubation(const double xRange, const double yRange )
{
	const Geom::Vector2d pertubation( (rand() % 10 ) / 10.0 * xRange,
				(rand() % 10 ) / 10.0 * yRange );
	(*this) += pertubation;
}

Point2d Point2d::getPertubated(const double xRange, const double yRange ) const
{
	Point2d pertubated = *(this);
	pertubated.addPertubation( xRange, yRange );
	return pertubated;
}