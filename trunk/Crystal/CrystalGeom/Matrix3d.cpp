#include "Matrix3d.h"
#include "Tolerances.h"
#include "Vector3d.h"

#include <cmath>
#include <cassert>

using namespace Crystal::Geom;


Matrix3d Matrix3d::product(const Matrix3d& rhs) {
		Vector3d lhs0( x00, x01, x02 );
		Vector3d lhs1( x10, x11, x12 );
		Vector3d lhs2( x20, x21, x22 );

		Vector3d rhs0( rhs.x00, rhs.x10, rhs.x20 );
		Vector3d rhs1( rhs.x01, rhs.x11, rhs.x21 );
		Vector3d rhs2( rhs.x02, rhs.x12, rhs.x22 );

		x00 = lhs0.getInnerProduct( rhs0 );
		x01 = lhs0.getInnerProduct( rhs1 );
		x02 = lhs0.getInnerProduct( rhs2 );

		x10 = lhs1.getInnerProduct( rhs0 );
		x11 = lhs1.getInnerProduct( rhs1 );
		x12 = lhs1.getInnerProduct( rhs2 );

		x20 = lhs2.getInnerProduct( rhs0 );
		x21 = lhs2.getInnerProduct( rhs1 );
		x22 = lhs2.getInnerProduct( rhs2 );

		return *this;
}

Matrix3d Matrix3d::getProduct(const Matrix3d& rhs) const
{
		Matrix3d matrix = *this;
		return matrix.product( rhs);
}

Matrix3d Matrix3d::scale(const double factor)
{
	x00 *= factor; x01 *= factor; x02 *= factor;
	x10 *= factor; x11 *= factor; x12 *= factor;
	x20 *= factor; x21 *= factor; x22 *= factor;
	return *this;
}

Matrix3d Matrix3d::getScaled(const double factor) const
{
	Matrix3d matrix = *this;
	return matrix.scale( factor);
}

Vector3d Matrix3d::getMult(const Vector3d& column) const
{
	return Vector3d( x00 * column.getX() + x01 * column.getY() + x02 * column.getZ(),
		x10 * column.getX() + x11 * column.getY() + x12 * column.getZ(),
		x20 * column.getX() + x21 * column.getY() + x22 * column.getZ() );
}

Vector3d Matrix3d::operator*(const Vector3d &rhs) const
{
	return getMult( rhs );
}

Matrix3d Matrix3d::operator+(const Matrix3d& rhs) const
{
	return getAdd( rhs);
}

const Matrix3d Matrix3d::operator+=(const Matrix3d& rhs)
{
	return add( rhs);
}

Matrix3d Matrix3d::operator-(const Matrix3d& rhs) const
{
	return getAdd( rhs.getScaled( -1.0) );
}

const Matrix3d Matrix3d::operator-=(const Matrix3d& rhs)
{
	return add( rhs.getScaled( -1.0) );
}

Matrix3d Matrix3d::operator*(const Matrix3d& rhs) const
{
	return getProduct( rhs);
}

const Matrix3d Matrix3d::operator*=(const Matrix3d& rhs)
{
	return product( rhs);
}