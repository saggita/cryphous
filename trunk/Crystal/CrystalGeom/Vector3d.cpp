#include "Vector3d.h"

#include "Point3d.h"
#include "Tolerances.h"
#include "Matrix3d.h"

#include <cmath>
#include <cassert>
#include <cstdlib>
#include <algorithm>

using namespace Crystal::Geom;

Vector3d::Vector3d(const Point3d& start, const Point3d& end) :
x( end.getX() - start.getX() ),
y( end.getY() - start.getY() ),
z( end.getZ() - start.getZ() )
{
}

Vector3d::Vector3d(const Vector3d& start, const Vector3d& end) :
x( end.getX() - start.getX() ),
y( end.getY() - start.getY() ),
z( end.getZ() - start.getZ() )
{
}

Vector3d::Vector3d(const Point3d& point) :
x( point.getX() ),
y( point.getY() ),
z( point.getZ() )
{
}

double Vector3d::getLength() const
{
	return ::sqrt( getLengthSquared() );
}

Vector3d Vector3d::normalize()
{
	const double length = getLength();
	assert( !Tolerances::isEqualAsDenominator( length ) );
	x /= length;
	y /= length;
	z /= length;
	assert( isNormalized() );
	return *this;
}

Vector3d Vector3d::getNormalized() const
{
	Vector3d vector = *(this);
	return vector.normalize();
}

bool Vector3d::isNormalized() const
{
	return Tolerances::isEqualAsDistance( getLength(), 1.0 );
}

bool Vector3d::equals(const Vector3d &rhs) const
{
	const Point3d posX( x, y, z );
	const Point3d posY( rhs.x, rhs.y, rhs.z );
	return posX.equals( posY );
}

bool Vector3d::isZero() const
{
	return Tolerances::isEqualAsDistance( getLength() );
}

void Vector3d::rotate(const Crystal::Geom::Matrix3d &matrix)
{
	Point3d point( x, y, z );
	*this = point.getRotated( matrix );
}

Vector3d Vector3d::getMult(const Matrix3d& matrix) const
{
	return Vector3d( x * matrix.x00 + y * matrix.x10 + z * matrix.x20,
		x * matrix.x01 + y * matrix.x11 + z * matrix.x21,
		x * matrix.x02 + y * matrix.x12 + z * matrix.x22 );
}

const Vector3d Vector3d::operator*(const Matrix3d& rhs) const
{
	return getMult( rhs);
}

double Vector3d::getMaxElement() const
{
	return std::max( std::max( x, y), z );
}

double Vector3d::getMinElement() const
{
	return std::min( std::min( x, y), z );
}