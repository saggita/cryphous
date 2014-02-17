#ifndef __CRYSTAL_GEOMETRY_MATRIX_3D_H__
#define __CRYSTAL_GEOMETRY_MATRIX_3D_H__

#include "Tolerances.h"

namespace Crystal {
	namespace Math {

class Matrix3d 
{
public:
	Matrix3d(void);
	
	Matrix3d(
		const float x00, const float x01, const float x02, 
		const float x10, const float x11, const float x12, 
		const float x20, const float x21, const float x22
		);

	~Matrix3d()
	{};

	void setZero();

	void setIdentity();

	bool isZero() const;
	
	bool Matrix3d::isIdentity() const;

	bool equals( const Matrix3d& rhs ) const;

	float getDeterminant() const;

	Matrix3d getInverse() const;

	Matrix3d product( const Matrix3d& rhs );

	Matrix3d getProduct( const Matrix3d& rhs ) const;

	Matrix3d scale( const float factor );

	Matrix3d getScaled( const float factor ) const;

	Matrix3d add( const Matrix3d& rhs );

	Matrix3d getAdd( const Matrix3d& rhs ) const;

	bool operator==( const Matrix3d& rhs ) const;

	Matrix3d operator+( const Matrix3d& rhs ) const;

	const Matrix3d operator+=(const Matrix3d& rhs);

	Matrix3d operator-( const Matrix3d& rhs ) const;
	
	const Matrix3d operator-=( const Matrix3d& rhs );
	
	Matrix3d operator*( const Matrix3d& rhs ) const;
	
	const Matrix3d operator*=( const Matrix3d& rhs );

	float getX00() const { return x00; }

	float getX01() const { return x01; }

	float getX02() const { return x02; }

	float getX10() const { return x10; }

	float getX11() const { return x11; }

	float getX12() const { return x12; }

private:
	float x00, x01, x02;
	float x10, x11, x12;
public:
	float x20, x21, x22;
};

	}
}

#endif