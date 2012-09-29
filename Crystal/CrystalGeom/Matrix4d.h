#ifndef __MATRIX_4D_H__
#define __MATRIX_4D_H__

#include <cassert>

#include "Tolerances.h"

namespace Crystal{
	namespace Geom{

class Matrix4d 
{
public:
	Matrix4d(void) :
	x00( 1.0), x01( 0.0), x02( 0.0), x03( 0.0),
	x10( 0.0), x11( 1.0), x12( 0.0), x13( 0.0),
	x20( 0.0), x21( 0.0), x22( 1.0), x23( 0.0),
	x30( 0.0), x31( 0.0), x32( 0.0), x33( 1.0)
	{
	}

	Matrix4d(const float x00, const float x01, const float x02, const float x03, 
					   const float x10, const float x11, const float x12, const float x13,
					   const float x20, const float x21, const float x22, const float x23,
					   const float x30, const float x31, const float x32, const float x33) :
	x00( x00), x01( x01), x02( x02), x03( x03),
	x10( x10), x11( x11), x12( x12), x13( x13),
	x20( x20), x21( x21), x22( x22), x23( x23),
	x30( x30), x31( x31), x32( x32), x33( x33)
	{
	}

	~Matrix4d() {};

	void setZero() {
		x00 = x01 = x02 = x03 = 0.0;
		x10 = x11 = x12 = x13 = 0.0;
		x20 = x21 = x22 = x23 = 0.0;
		x30 = x31 = x32 = x33 = 0.0;
	}

	void setIdentity() {
		x00 = 1.0; x01 = 0.0; x02 = 0.0; x03 = 0.0;
		x10 = 0.0; x11 = 1.0; x12 = 0.0; x13 = 0.0;
		x20 = 0.0; x21 = 0.0; x22 = 1.0; x23 = 0.0;
		x30 = 0.0; x31 = 0.0; x32 = 0.0; x33 = 1.0;
	}
	
	bool isZero() const {
		Matrix4d zeroMatrix;
		zeroMatrix.setZero();
		return this->equals( zeroMatrix );
	}
	
	bool Matrix4d::isIdentity() const {
		Matrix4d identityMatrix;
		identityMatrix.setIdentity();
		return this->equals( identityMatrix );
	}

	void setTranslate(const float x, const float y, const float z) {
		x03 = x;
		x13 = y;
		x23 = z;
	}

	void translate(const float x, const float y, const float z) {
		Matrix4d matrix;
		matrix.translate( x, y, z);
		(*this) *= matrix;
	}

	void setRotateX(const float angle) {
		x11 = ::cos( angle );
		x21 = ::sin( angle );
		x12 = -::sin( angle );
		x22 = ::cos( angle );
	}

	void rotateX(const float angle) {
		Matrix4d matrix;
		matrix.setRotateX( angle );
		(*this) *= matrix;
	}

	void setRotateY(const float angle) {
		x00 = ::cos( angle );
		x20 = -::sin( angle );
		x02 = ::sin( angle );
		x22 = ::cos( angle );
	}

	void rotateY(const float angle) {
		Matrix4d matrix;
		matrix.setRotateY( angle );
		(*this) *= matrix;
	}

	void setRotateZ(const float angle) {
		x00 = ::cos( angle );
		x10 = ::sin( angle );
		x01 = -::sin( angle );
		x11 = ::cos( angle );
	}

	void rotateZ(const float angle) {
		Matrix4d matrix;
		matrix.setRotateZ( angle );
		(*this) *= matrix;
	}

	bool equals(const Matrix4d& rhs) const {
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

	Matrix4d Matrix4d::product(const Matrix4d& rhs) { return *this = getProduct(rhs); }

	Matrix4d Matrix4d::getProduct(const Matrix4d& rhs) const {
		return Matrix4d( 
				x00 * rhs.x00 + x01 * rhs.x10 + x02 * rhs.x20 + x03 * rhs.x30,
				x00 * rhs.x01 + x01 * rhs.x11 + x02 * rhs.x21 + x03 * rhs.x31,
				x00 * rhs.x02 + x01 * rhs.x12 + x02 * rhs.x22 + x03 * rhs.x32,
				x00 * rhs.x03 + x01 * rhs.x13 + x02 * rhs.x23 + x03 * rhs.x33,
				x10 * rhs.x00 + x11 * rhs.x10 + x12 * rhs.x20 + x13 * rhs.x30,
				x10 * rhs.x01 + x11 * rhs.x11 + x12 * rhs.x21 + x13 * rhs.x31,
				x10 * rhs.x02 + x11 * rhs.x12 + x12 * rhs.x22 + x13 * rhs.x32,
				x10 * rhs.x03 + x11 * rhs.x13 + x12 * rhs.x23 + x13 * rhs.x33,
				x20 * rhs.x00 + x21 * rhs.x10 + x22 * rhs.x20 + x23 * rhs.x30,
				x20 * rhs.x01 + x21 * rhs.x11 + x22 * rhs.x21 + x23 * rhs.x31,
				x20 * rhs.x02 + x21 * rhs.x12 + x22 * rhs.x22 + x23 * rhs.x32,
				x20 * rhs.x03 + x21 * rhs.x13 + x22 * rhs.x23 + x23 * rhs.x33,
				x30 * rhs.x00 + x31 * rhs.x10 + x32 * rhs.x20 + x33 * rhs.x30,
				x30 * rhs.x01 + x31 * rhs.x11 + x32 * rhs.x21 + x33 * rhs.x31,
				x30 * rhs.x02 + x31 * rhs.x12 + x32 * rhs.x22 + x33 * rhs.x32,
				x30 * rhs.x03 + x31 * rhs.x13 + x32 * rhs.x23 + x33 * rhs.x33);
	}

	Matrix4d scale(const float factor) {
		x00 *= factor; x01 *= factor; x02 *= factor; x03 *= factor;
		x10 *= factor; x11 *= factor; x12 *= factor; x13 *= factor;
		x20 *= factor; x21 *= factor; x22 *= factor; x23 *= factor;
		x30 *= factor; x31 *= factor; x32 *= factor; x33 *= factor;
		return *this;
	}

	Matrix4d Matrix4d::getScaled(const float factor) const {
		Matrix4d matrix = *this;
		return matrix.scale( factor);
	}

	Matrix4d add(const Matrix4d& rhs) {
		x00 += rhs.x00;
		x01 += rhs.x01;
		x02 += rhs.x02;
		x03 += rhs.x03;

		x10 += rhs.x10;
		x11 += rhs.x11;
		x12 += rhs.x12;
		x13 += rhs.x13;

		x20 += rhs.x20;
		x21 += rhs.x21;
		x22 += rhs.x22;
		x23 += rhs.x23;

		x30 += rhs.x30;
		x31 += rhs.x31;
		x32 += rhs.x32;
		x33 += rhs.x33;

		return *this;
	}
	
	Matrix4d getAdd(const Matrix4d& rhs) const {
		Matrix4d matrix = *this;
		return matrix.add( rhs);
	}

	bool operator==(const Matrix4d& rhs) const { return this->equals(rhs); }

	Matrix4d Matrix4d::operator+(const Matrix4d& rhs) const { return getAdd( rhs); }

	const Matrix4d Matrix4d::operator+=(const Matrix4d& rhs) { return add( rhs); }

	Matrix4d operator-(const Matrix4d& rhs) const { return getAdd( rhs.getScaled( -1.0) ); }
	
	const Matrix4d Matrix4d::operator-=(const Matrix4d& rhs) { return add( rhs.getScaled( -1.0) ); }
	
	Matrix4d Matrix4d::operator*(const Matrix4d& rhs) const { return getProduct( rhs); }
	
	const Matrix4d Matrix4d::operator*=(const Matrix4d& rhs) { return product( rhs); }

public:
	float x00, x01, x02, x03;
	float x10, x11, x12, x13;
	float x20, x21, x22, x23;
	float x30, x31, x32, x33;
};

	}
}

#endif