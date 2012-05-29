#ifndef __MATRIX_2D_H__
#define __MATRIX_2D_H__

namespace Crystal{
	namespace Geom{
		class Vector2d;

class Matrix2d
{
public:
	
	Matrix2d(void);

	Matrix2d(const double x00, const double x01,
		const double x10, const double x11);

	~Matrix2d() {};

	void setZero();

	void setIdentity();

	void setRotate(const double angle);

	Matrix2d getInverse() const;

	Matrix2d getTranspose() const;

	Matrix2d getProduct(const Matrix2d& rhs) const;

	Matrix2d product(const Matrix2d& rhs);

	Matrix2d add(const Matrix2d& rhs);

	Matrix2d getAdd(const Matrix2d& rhs) const;

	Vector2d getMult(const Vector2d& column) const;

	double getDeterminant() const;

	bool isZero() const;

	bool isIdentity() const;

	bool equals(const Matrix2d& rhs) const;

	Matrix2d scale(const double factor);

	Matrix2d getScaled(const double factor) const;

	bool operator==(const Matrix2d& rhs) const { return this->equals(rhs); }

	Matrix2d operator+(const Matrix2d& rhs) const;

	const Matrix2d operator+=(const Matrix2d& rhs);

	Matrix2d operator-(const Matrix2d& rhs) const;

	const Matrix2d operator-=(const Matrix2d& rhs);

	Matrix2d operator*(const Matrix2d& rhs) const;

	const Matrix2d operator*=(const Matrix2d& rhs);

	Vector2d operator*(const Vector2d& rhs) const;

public:
	double x00;
	double x01;
	double x10;
	double x11;
};

	}
}

#endif