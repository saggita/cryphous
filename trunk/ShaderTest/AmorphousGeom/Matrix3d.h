#ifndef __MATRIX_3D_H__
#define __MATRIX_3D_H__

namespace Amorphous{
	namespace Geom{

template <typename T = double>
class Matrix3d 
{
public:
	Matrix3d(void):
		x00( 0.0), x01( 0.0), x02( 0.0),
		x10( 0.0), x11( 0.0), x12( 0.0),
		x20( 0.0), x21( 0.0), x22( 0.0)
		{}

	Matrix3d(const T x00, const T x01, const T x02,
		const T x10, const T x11, const T x12,
		const T x20, const T x21, const T x22) :
		x00( x00), x01( x01), x02( x02),
		x10( x10), x11( x11), x12( x12),
		x20( x20), x21( x21), x22( x22)
	{}

	~Matrix3d() {};

	void setZero() {
		x00 = x01 = x02 = 0.0;
		x10 = x11 = x12 = 0.0;
		x20 = x21 = x22 = 0.0;
		assert( isZero() );
	}

	void setIdentity() {
		x00 = 1.0; x01 = 0.0; x02 = 0.0;
		x10 = 0.0; x11 = 1.0; x12 = 0.0;
		x20 = 0.0; x21 = 0.0; x22 = 1.0;
		assert( isIdentity() );
	}

	bool isZero() const {
		Matrix3d zeroMatrix;
		return this->equals( zeroMatrix );
	}

	bool isIdentity() const {
		Matrix3d identityMatrix( 1.0, 0.0, 0.0,
							0.0, 1.0, 0.0,
							0.0, 0.0, 1.0);
		return this->equals( identityMatrix );
	}

	bool equals(const Matrix3d& rhs) const {
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

	T getDeterminant() const {
		return x00 * x11 * x22
			+ x02 * x10 * x21
			+ x20 * x01 * x12
			- x02 * x11 * x20
			- x00 * x12 * x21
			- x01 * x10 * x22;
	}

	Matrix3d getInverse() const {
		const T denominator = getDeterminant();
	
		const T i00 = x11 * x22 - x12 * x21;
		const T i01 = x21 * x02 - x22 * x01;
		const T i02 = x01 * x12 - x02 * x11;

		const T i10 = x12 * x20 - x10 * x22;
		const T i11 = x22 * x00 - x20 * x02;
		const T i12 = x02 * x10 - x00 * x12;

		const T i20 = x10 * x21 - x11 * x20;
		const T i21 = x20 * x01 - x21 * x00;
		const T i22 = x00 * x11 - x01 * x10;

		Matrix3d matrix( i00, i01, i02,
			i10, i11, i12,
			i20, i21, i22 );
		matrix.scale( 1.0 / denominator );
		return matrix;
	}

	Matrix3d product(const Matrix3d& rhs) {
		const T i00 = x00 * rhs.x00 + x01 * rhs.x10 + x02 * rhs.x20;
		const T i01 = x00 * rhs.x01 + x01 * rhs.x11 + x02 * rhs.x21;
		const T i02 = x00 * rhs.x02 + x01 * rhs.x12 + x02 * rhs.x22;

		const T i10 = x10 * rhs.x00 + x11 * rhs.x10 + x12 * rhs.x20;
		const T i11 = x10 * rhs.x01 + x11 * rhs.x11 + x12 * rhs.x21;
		const T i12 = x10 * rhs.x02 + x11 * rhs.x12 + x12 * rhs.x22;

		const T i20 = x20 * rhs.x00 + x21 * rhs.x10 + x22 * rhs.x20;
		const T i21 = x20 * rhs.x01 + x21 * rhs.x11 + x22 * rhs.x21;
		const T i22 = x20 * rhs.x02 + x21 * rhs.x12 + x22 * rhs.x22;

		return *this = Matrix3d(i00, i01, i02,
			i10, i11, i12,
			i20, i21, i22);
	}

	Matrix3d getProduct(const Matrix3d& rhs) const {
		Matrix3d matrix = *this;
		return matrix.product( rhs);
	}

	void setRotateX(const T angle) {
		*(this) = Matrix3d(
			1.0, 0.0, 0.0,
			0.0, cos(angle), -sin(angle),
			0.0, sin(angle), cos(angle )
		);
	}

	void setRotateY(const T angle) {
		*(this) = Matrix3d(
			cos(angle), 0.0, sin(angle),
			0.0, 1.0, 0.0,
			-sin(angle), 0.0, cos(angle)
		);
	}

	void setRotateZ(const T angle) {
		*(this) = Matrix3d(
			cos(angle), -sin(angle), 0.0,
			sin(angle), cos(angle), 0.0,
			0.0, 0.0, 1.0
			);
	}

	Matrix3d scale(const T factor) {
		x00 *= factor; x01 *= factor; x02 *= factor;
		x10 *= factor; x11 *= factor; x12 *= factor;
		x20 *= factor; x21 *= factor; x22 *= factor;
		return *this;
	}

	Matrix3d getScaled(const T factor) const {
		Matrix3d matrix = *this;
		return matrix.scale( factor);
	}

	Matrix3d add(const Matrix3d& rhs) {
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

	Matrix3d getAdd(const Matrix3d& rhs) const{
		Matrix3d matrix = *this;
		return matrix.add( rhs);
	}

	bool operator==(const Matrix3d& rhs) const { return this->equals(rhs); }

	Matrix3d operator+(const Matrix3d& rhs) const { return getAdd( rhs); }

	const Matrix3d operator+=(const Matrix3d& rhs) { return add( rhs); }

	Matrix3d operator-(const Matrix3d& rhs) const { return getAdd( rhs.getScaled( -1.0) ); }

	const Matrix3d operator-=(const Matrix3d& rhs) { return add( rhs.getScaled( -1.0) ); }

	Matrix3d operator*(const Matrix3d& rhs) const { return getProduct( rhs); }

	const Matrix3d operator*=(const Matrix3d& rhs) { return product( rhs); }

public:
	T x00, x01, x02;
	T x10, x11, x12;
	T x20, x21, x22;
};

	}
}

#endif