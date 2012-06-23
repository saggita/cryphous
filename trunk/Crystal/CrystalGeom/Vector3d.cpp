#include "Vector3d.h"

#include "Tolerances.h"
#include "Matrix3d.h"

#include <cmath>
#include <cassert>
#include <cstdlib>
#include <algorithm>

using namespace Crystal::Geom;


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
	return Tolerances::isEqualAsDistance( getDistance( rhs ) );
}

bool Vector3d::isZero() const
{
	return Tolerances::isEqualAsDistance( getLength() );
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