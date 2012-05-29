#include "Vector2d.h"

#include "Point2d.h"
#include "Matrix2d.h"
#include "Tolerances.h"

#include <cmath>
#include <cassert>
#include <cstdlib>

using namespace Crystal::Geom;

Vector2d::Vector2d(const Point2d& start, const Point2d& end) :
x( end.getX() - start.getX() ),
y( end.getY() - start.getY() )
{
}

Vector2d::Vector2d(const Vector2d& start, const Vector2d& end) :
x( end.getX() - start.getX() ),
y( end.getY() - start.getY() )
{
}

Vector2d::Vector2d(const Point2d& point) :
x( point.getX() ),
y( point.getY() )
{
}

double Vector2d::getLength() const
{
	return ::sqrt( getLengthSquared() );
}

Vector2d Vector2d::normalize()
{
	const double length = getLength();
	assert( !Tolerances::isEqualAsDenominator( length ) );
	x /= length;
	y /= length;
	assert( isNormalized() );
	return *this;
}

Vector2d Vector2d::getNormalized() const
{
	Vector2d vector = *(this);
	return vector.normalize();
}

bool Vector2d::isNormalized() const
{
	return Tolerances::isEqualAsDistance( getLength(), 1.0 );
}

bool Vector2d::equals(const Vector2d &rhs) const
{
	const Point2d posX( x, y );
	const Point2d posY( rhs.x, rhs.y );
	return posX.equals( posY );
}

bool Vector2d::isZero() const
{
	return Tolerances::isEqualAsDistance( getLength() );
}

Vector2d Vector2d::getMult(const Matrix2d& matrix) const
{
	return Vector2d( x * matrix.x00 + y * matrix.x10,
		x * matrix.x01 + y * matrix.x11 );
}

const Vector2d Vector2d::operator*(const Matrix2d& rhs) const
{
	return getMult( rhs);
}