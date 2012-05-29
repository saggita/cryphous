#ifndef __MATRIX_3D_H__
#define __MATRIX_3D_H__

namespace Crystal{
	namespace Geom{
		class Vector3d;

class Matrix3d 
{
public:
	Matrix3d(void);

	Matrix3d(const double x00, const double x01, const double x02,
		const double x10, const double x11, const double x12,
		const double x20, const double x21, const double x22);

	~Matrix3d() {};

	void setZero();

	void setIdentity();

	bool isZero() const;

	bool isIdentity() const;

	bool equals(const Matrix3d& rhs) const;

	double getDeterminant() const;

	Matrix3d getInverse() const;

	Matrix3d product(const Matrix3d& rhs);

	Matrix3d getProduct(const Matrix3d& rhs) const;

	void setRotateX(const double angle);

	void setRotateY(const double angle);

	void setRotateZ(const double angle);

	Matrix3d scale(const double factor);

	Matrix3d getScaled(const double factor) const;

	Matrix3d add(const Matrix3d& rhs);

	Matrix3d getAdd(const Matrix3d& rhs) const;

	bool operator==(const Matrix3d& rhs) const { return this->equals(rhs); }

	Vector3d getMult(const Vector3d& column) const;

	Vector3d operator*(const Vector3d& rhs) const;

	Matrix3d operator+(const Matrix3d& rhs) const;

	const Matrix3d operator+=(const Matrix3d& rhs);

	Matrix3d operator-(const Matrix3d& rhs) const;

	const Matrix3d operator-=(const Matrix3d& rhs);

	Matrix3d operator*(const Matrix3d& rhs) const;

	const Matrix3d operator*=(const Matrix3d& rhs);

public:
	double x00, x01, x02;
	double x10, x11, x12;
	double x20, x21, x22;
};

	}
}

#endif