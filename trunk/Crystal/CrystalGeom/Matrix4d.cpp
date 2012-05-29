#include "Matrix4d.h"

#include "Tolerances.h"

#include <cassert>

using namespace Crystal::Geom;

Matrix4d::Matrix4d(void) :
x00( 0.0), x01( 0.0), x02( 0.0), x03( 0.0),
x10( 0.0), x11( 0.0), x12( 0.0), x13( 0.0),
x20( 0.0), x21( 0.0), x22( 0.0), x23( 0.0),
x30( 0.0), x31( 0.0), x32( 0.0), x33( 0.0)
{
}

Matrix4d::Matrix4d(const double x00, const double x01, const double x02, const double x03,
				   const double x10, const double x11, const double x12, const double x13, 
				   const double x20, const double x21, const double x22, const double x23,
				   const double x30, const double x31, const double x32, const double x33) :
x00(x00), x01(x01), x02(x02), x03(x03),
x10(x10), x11(x11), x12(x12), x13(x13),
x20(x20), x21(x21), x22(x22), x23(x23),
x30(x30), x31(x31), x32(x32), x33(x33)
{
}

void Matrix4d::setZero()
{
	*this = Matrix4d( 
		0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0 );
	assert( isZero() );
}

void Matrix4d::setIdentity()
{
	*this = Matrix4d(
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0 );
	assert( isIdentity() );
}

bool Matrix4d::isZero() const
{
	Matrix4d zeroMatrix;
	return this->equals( zeroMatrix );
}

bool Matrix4d::isIdentity() const
{
	Matrix4d identityMatrix( 1.0, 0.0, 0.0, 0.0,
							0.0, 1.0, 0.0, 0.0,
							0.0, 0.0, 1.0, 0.0,
							0.0, 0.0, 0.0, 1.0);
	return this->equals( identityMatrix );
}

double Matrix4d::getDeterminant() const
{
	assert( false );
	return 0.0;
}

bool Matrix4d::equals( const Matrix4d& rhs ) const
{
	return 
		Tolerances::isEqualAsDenominator( x00, rhs.x00 ) &&
		Tolerances::isEqualAsDenominator( x01, rhs.x01 ) &&
		Tolerances::isEqualAsDenominator( x02, rhs.x02 ) &&
		Tolerances::isEqualAsDenominator( x03, rhs.x03 ) &&
		Tolerances::isEqualAsDenominator( x10, rhs.x10 ) &&
		Tolerances::isEqualAsDenominator( x11, rhs.x11 ) &&
		Tolerances::isEqualAsDenominator( x12, rhs.x12 ) &&
		Tolerances::isEqualAsDenominator( x13, rhs.x13 ) &&
		Tolerances::isEqualAsDenominator( x20, rhs.x20 ) &&
		Tolerances::isEqualAsDenominator( x21, rhs.x21 ) &&
		Tolerances::isEqualAsDenominator( x22, rhs.x22 ) &&
		Tolerances::isEqualAsDenominator( x23, rhs.x23 ) &&	
		Tolerances::isEqualAsDenominator( x30, rhs.x30 ) &&
		Tolerances::isEqualAsDenominator( x31, rhs.x31 ) &&
		Tolerances::isEqualAsDenominator( x32, rhs.x32 ) &&
		Tolerances::isEqualAsDenominator( x33, rhs.x33 );
}