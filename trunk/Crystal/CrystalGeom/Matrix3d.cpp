#include "Matrix3d.h"
#include "Tolerances.h"
#include "Vector3d.h"

#include <cmath>
#include <cassert>

using namespace Crystal::Geom;

Matrix3d::Matrix3d(void) :
x00( 0.0), x01( 0.0), x02( 0.0),
x10( 0.0), x11( 0.0), x12( 0.0),
x20( 0.0), x21( 0.0), x22( 0.0)
{
}

Matrix3d::Matrix3d(const double x00, const double x01, const double x02, 
				   const double x10, const double x11, const double x12, 
				   const double x20, const double x21, const double x22) :
x00( x00), x01( x01), x02( x02),
x10( x10), x11( x11), x12( x12),
x20( x20), x21( x21), x22( x22)
{
}

void Matrix3d::setZero()
{
	x00 = x01 = x02 = 0.0;
	x10 = x11 = x12 = 0.0;
	x20 = x21 = x22 = 0.0;
	assert( isZero() );
}

void Matrix3d::setIdentity()
{
	x00 = 1.0; x01 = 0.0; x02 = 0.0;
	x10 = 0.0; x11 = 1.0; x12 = 0.0;
	x20 = 0.0; x21 = 0.0; x22 = 1.0;
	assert( isIdentity() );
}

bool Matrix3d::isZero() const
{
	Matrix3d zeroMatrix;
	return this->equals( zeroMatrix );
}

bool Matrix3d::isIdentity() const
{
	Matrix3d identityMatrix( 1.0, 0.0, 0.0,
							0.0, 1.0, 0.0,
							0.0, 0.0, 1.0);
	return this->equals( identityMatrix );
}

bool Matrix3d::equals( const Matrix3d& rhs ) const
{
	return
		Tolerances::isEqualAsDenominator( x00, rhs.x00 ) &&
		Tolerances::isEqualAsDenominator( x01, rhs.x01 ) &&
		Tolerances::isEqualAsDenominator( x02, rhs.x02 ) &&
		Tolerances::isEqualAsDenominator( x10, rhs.x10 ) &&
		Tolerances::isEqualAsDenominator( x11, rhs.x11 ) &&
		Tolerances::isEqualAsDenominator( x12, rhs.x12 ) &&
		Tolerances::isEqualAsDenominator( x20, rhs.x20 ) &&
		Tolerances::isEqualAsDenominator( x21, rhs.x21 ) &&
		Tolerances::isEqualAsDenominator( x22, rhs.x22 );
}

double Matrix3d::getDeterminant() const
{
	return x00 * x11 * x22
		+ x02 * x10 * x21
		+ x20 * x01 * x12
		- x02 * x11 * x20
		- x00 * x12 * x21
		- x01 * x10 * x22;
}

Matrix3d Matrix3d::getInverse() const
{
	const double denominator = getDeterminant();
	assert( !Tolerances::isEqualAsDenominator( denominator ) );
	
	const double i00 = x11 * x22 - x12 * x21;
	const double i01 = x21 * x02 - x22 * x01;
	const double i02 = x01 * x12 - x02 * x11;

	const double i10 = x12 * x20 - x10 * x22;
	const double i11 = x22 * x00 - x20 * x02;
	const double i12 = x02 * x10 - x00 * x12;

	const double i20 = x10 * x21 - x11 * x20;
	const double i21 = x20 * x01 - x21 * x00;
	const double i22 = x00 * x11 - x01 * x10;

	Matrix3d matrix( i00, i01, i02,
		i10, i11, i12,
		i20, i21, i22 );
	matrix.scale( 1.0 / denominator );
	return matrix;
}

Matrix3d Matrix3d::add(const Matrix3d& rhs)
{
	x00 += rhs.x00;
	x01 += rhs.x01;
	x02 += rhs.x02;

	x10 += rhs.x10;
	x11 += rhs.x11;
	x12 += rhs.x12;

	x20 += rhs.x20;
	x21 += rhs.x21;
	x22 += rhs.x22;

	return *this;
}

Matrix3d Matrix3d::getAdd(const Matrix3d& rhs) const
{
	Matrix3d matrix = *this;
	return matrix.add( rhs);
}

Matrix3d Matrix3d::product(const Matrix3d& rhs)
{
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

void Matrix3d::setRotateX(const double angle)
{
	*(this) = Matrix3d(
		1.0, 0.0, 0.0,
		0.0, cos(angle), -sin(angle),
		0.0, sin(angle), cos(angle )
		);
}

void Matrix3d::setRotateY(const double angle)
{
	*(this) = Matrix3d(
		cos(angle), 0.0, sin(angle),
		0.0, 1.0, 0.0,
		-sin(angle), 0.0, cos(angle)
		);
}

void Matrix3d::setRotateZ(const double angle)
{
	*(this) = Matrix3d(
		cos(angle), -sin(angle), 0.0,
		sin(angle), cos(angle), 0.0,
		0.0, 0.0, 1.0
		);
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