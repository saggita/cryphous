#include "Vector4d.h"

#include "Point4d.h"
#include "Tolerances.h"
#include "Matrix4d.h"

#include "Vector3d.h"

#include <cmath>
#include <cassert>
#include <cstdlib>

using namespace Crystal::Geom;

Vector4d::Vector4d(const Point4d& start, const Point4d& end) :
x( end.getX() - start.getX() ),
y( end.getY() - start.getY() ),
z( end.getZ() - start.getZ() ),
w( end.getW() - start.getW() )
{
}

Vector4d::Vector4d(const Vector4d& start, const Vector4d& end) :
x( end.getX() - start.getX() ),
y( end.getY() - start.getY() ),
z( end.getZ() - start.getZ() ),
w( end.getW() - start.getW() )
{
}

Vector4d::Vector4d(const Point4d& point) :
x( point.getX() ),
y( point.getY() ),
z( point.getZ() ),
w( point.getW() )
{
}

double Vector4d::getLength() const
{
	return ::sqrt( getLengthSquared() );
}

Vector4d Vector4d::normalize()
{
	const double length = getLength();
	assert( !Tolerances::isEqualAsDenominator( length ) );
	x /= length;
	y /= length;
	z /= length;
	w /= length;
	assert( isNormalized() );
	return *this;
}

Vector4d Vector4d::getNormalized() const
{
	Vector4d vector = *(this);
	return vector.normalize();
}

bool Vector4d::isNormalized() const
{
	return Tolerances::isEqualAsDistance( getLength(), 1.0 );
}

bool Vector4d::equals(const Vector4d &rhs) const
{
	const Point4d posX( x, y, z, w );
	const Point4d posY( rhs.x, rhs.y, rhs.z, rhs.w );
	return posX.equals( posY );
}

bool Vector4d::isZero() const
{
	return Tolerances::isEqualAsDistance( getLength() );
}

void Vector4d::rotate(const Crystal::Geom::Matrix4d &matrix)
{
	Point4d point( x, y, z, w );
	point.rotate( matrix );
}

Vector3d Vector4d::getVector3d() const
{
	assert( !Tolerances::isEqualAsDenominator( w ) );
	return Vector3d( x/w, y/w, z/w );
}