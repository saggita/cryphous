#include "Matrix2d.h"

#include "Vector2d.h"
#include "Tolerances.h"

#include <cassert>
#include <cmath>

using namespace Crystal::Geom;

Matrix2d::Matrix2d(void) :
x00( 0.0), x01( 0.0),
x10( 0.0), x11( 0.0)
{
}

Matrix2d::Matrix2d(const double x00, const double x01, const double x10, const double x11) :
x00( x00), x01( x01),
x10( x10), x11( x11)
{
}

void Matrix2d::setZero()
{
	x00 = 0.0; x01 = 0.0;
	x10 = 0.0; x11 = 0.0;
	assert( isZero() );
}

void Matrix2d::setIdentity()
{
	setZero();

	x00 = 1.0;
	x11 = 1.0;
	assert( isIdentity() );
}

void Matrix2d::setRotate(const double angle)
{
	x00 = ::cos( angle ), x01 = -::sin( angle );
	x10 = ::sin( angle ), x11 = ::cos( angle );
}

Matrix2d Matrix2d::getInverse() const
{
	const double dominator = x00 * x11 - x01 * x10;
	assert( !Tolerances::isEqualAsDenominator( dominator ) );

	Matrix2d matrix( x11, -x01,
		-x10, x00 );
	matrix.scale( 1.0 / dominator );

	return matrix;
}

Matrix2d Matrix2d::getTranspose() const
{
	return Matrix2d( x00, x10, x01, x11 );
}

Matrix2d Matrix2d::product(const Matrix2d& rhs)
{
	const double x00 = this->x00 * rhs.x00 + this->x01 * rhs.x10;
	const double x01 = this->x00 * rhs.x01 + this->x01 * rhs.x11;
	const double x10 = this->x10 * rhs.x00 + this->x11 * rhs.x10;
	const double x11 = this->x10 * rhs.x01 + this->x11 * rhs.x11;

	this->x00 = x00;
	this->x01 = x01;
	this->x10 = x10;
	this->x11 = x11;
	
	return *this;
}

Matrix2d Matrix2d::getProduct(const Matrix2d &rhs) const
{
	Matrix2d matrix = *this;
	return matrix.product( rhs);
}

Matrix2d Matrix2d::add(const Matrix2d& rhs)
{
	x00 += rhs.x00;
	x01 += rhs.x01;
	x10 += rhs.x10;
	x11 += rhs.x11;
	return *this;
}

Matrix2d Matrix2d::getAdd(const Matrix2d& rhs) const
{
	Matrix2d matrix = *this;
	return matrix.add(rhs);
}

Vector2d Matrix2d::getMult(const Vector2d& column) const
{
	return Vector2d( x00 * column.getX() + x01 * column.getY(),
		x10 * column.getX() + x11 * column.getY() );
}

double Matrix2d::getDeterminant() const
{
	return x00 * x11 - x01 * x10;
}

bool Matrix2d::isZero() const
{
	Matrix2d zeroMatrix;
	return this->equals( zeroMatrix );
}

bool Matrix2d::isIdentity() const
{
	Matrix2d identityMatrix( 1.0, 0.0, 0.0, 1.0);
	return this->equals( identityMatrix );
}

bool Matrix2d::equals( const Matrix2d& rhs ) const
{
	return Tolerances::isEqualAsDenominator( x00, rhs.x00  ) &&
		Tolerances::isEqualAsDenominator( x01, rhs.x01 ) &&
		Tolerances::isEqualAsDenominator( x10, rhs.x10 ) &&
		Tolerances::isEqualAsDenominator( x11, rhs.x11 );
}

Matrix2d Matrix2d::scale(const double factor)
{
	x00 *= factor; x01 *= factor;
	x10 *= factor; x11 *= factor;
	return *this;
}

Matrix2d Matrix2d::getScaled(const double factor) const
{
	Matrix2d matrix = *this;
	return matrix.scale( factor);
}

Matrix2d Matrix2d::operator+(const Matrix2d& rhs) const
{
	return getAdd( rhs);
}

const Matrix2d Matrix2d::operator+=(const Matrix2d& rhs)
{
	return add( rhs);
}

Matrix2d Matrix2d::operator-(const Matrix2d& rhs) const
{
	return getAdd( rhs.getScaled( -1.0) );
}

const Matrix2d Matrix2d::operator-=(const Matrix2d& rhs)
{
	return add( rhs.getScaled( -1.0) );
}

Matrix2d Matrix2d::operator*(const Matrix2d& rhs) const
{
	return getProduct( rhs);
}

const Matrix2d Matrix2d::operator*=(const Matrix2d& rhs)
{
	return product( rhs);
}

Vector2d Matrix2d::operator*(const Vector2d& rhs) const
{
	return getMult( rhs);
}