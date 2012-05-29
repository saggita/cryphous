#ifndef __MATRIX_4D_H__
#define __MATRIX_4D_H__

namespace Crystal{
	namespace Geom{

class Matrix4d
{
public:
	
	Matrix4d(void);

	Matrix4d(const double x00, const double x01, const double x02, const double x03,
		const double x10, const double x11, const double x12, const double x13,
		const double x20, const double x21, const double x22, const double x23,
		const double x30, const double x31, const double x32, const double x33);

	~Matrix4d() {};

	void setZero();

	void setIdentity();

	bool isZero() const;

	bool isIdentity() const;

	bool equals(const Matrix4d& rhs) const;

	double getDeterminant() const;
	
	bool operator==(const Matrix4d& rhs) const { return this->equals(rhs); }

public:
	double x00,x01,x02,x03;
	double x10,x11,x12,x13;
	double x20,x21,x22,x23;
	double x30,x31,x32,x33;
};

	}
}

#endif