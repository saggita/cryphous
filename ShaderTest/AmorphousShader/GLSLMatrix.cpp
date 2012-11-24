#include "GLSLMatrix.h"

#include <cassert>
#include <cmath>

using namespace Amorphous::Geom;
using namespace Amorphous::Shader;

GLSLMatrix::GLSLMatrix(void)
{
	setIdentityMatrix();
}

GLSLMatrix::GLSLMatrix(const Matrix3d<float>& matrix)
{
	setIdentityMatrix();
	x[0] = matrix.x00;
	x[1] = matrix.x10;
	x[2] = matrix.x20;
	x[4] = matrix.x10;
	x[5] = matrix.x11;
	x[6] = matrix.x12;
	x[8] = matrix.x20;
	x[9] = matrix.x21;
	x[10] = matrix.x22;
}

GLSLMatrix::~GLSLMatrix(void)
{
}

void GLSLMatrix::setIdentityMatrix()
{
	x[0] = 1.0; x[1] = 0.0; x[2] = 0.0; x[3] = 0.0;
	x[4] = 0.0; x[5] = 1.0; x[6] = 0.0; x[7] = 0.0;
	x[8] = 0.0; x[9] = 0.0; x[10] = 1.0; x[11] = 0.0;
	x[12] = 0.0; x[13] = 0.0; x[14] = 0.0; x[15] = 1.0;
}

void GLSLMatrix::setOrthogonalMatrix(const float left, const float right, const float bottom, const float top, const float nearZ, const float farZ)
{
	const float dx = right - left;
	const float dy = top - bottom;
	const float dz = farZ - nearZ;
	setIdentityMatrix();
	x[0] =  2.0f / dx;
	x[5] =  2.0f / dy;
	x[10] = -2.0f / dz;
	x[12] = -(right + left) / dx; x[13] = -(top + bottom) / dy; x[14] = -(farZ + nearZ) / dz;
}

void GLSLMatrix::setPerspectiveMatrix(const float left, const float right, const float bottom, const float top, const float nearZ, const float farZ)
{
	const float dx = right - left;
	const float dy = top - bottom;
	const float dz = farZ - nearZ;
	x[ 0] =  2.0f / dx;
	x[ 5] =  2.0f / dy;
	x[10] = -1.0f / dz;
	x[11] = -1.0f;
	x[12] = -(right + left) / dx;
	x[13] = -(bottom + top) / dy;
	x[14] = -nearZ / dz;	
}

void GLSLMatrix::translate(const float x, const float y, const float z )
{
	GLSLMatrix translateMatrix;
	translateMatrix.setTranslate(x,y,z);
	(*this) *= translateMatrix;
}

void GLSLMatrix::setTranslate(const float x, const float y, const float z)
{
	this->x[12] = x;
	this->x[13] = y;
	this->x[14] = z;
}

void GLSLMatrix::rotateX(const float angle)
{
	GLSLMatrix rotateMatrix;
	rotateMatrix.setRotateX(angle);
	(*this) *= rotateMatrix;
}

void GLSLMatrix::setRotateX(const float angle)
{
	this->x[5] = ::cos( angle );
	this->x[6] = ::sin( angle );
	this->x[9] = -::sin( angle );
	this->x[10] = ::cos( angle );
}

void GLSLMatrix::rotateY(const float angle)
{
	GLSLMatrix rotateMatrix;
	rotateMatrix.setRotateY(angle);
	(*this) *= rotateMatrix;
}

void GLSLMatrix::setRotateY(const float angle)
{
	this->x[0] = ::cos( angle );
	this->x[2] = -::sin( angle );
	this->x[8] = ::sin( angle );
	this->x[10] = cos(angle);
}

void GLSLMatrix::setRotateZ(const float angle)
{
	this->x[0] = ::cos( angle );
	this->x[1] = ::sin( angle );
	this->x[4] = -::sin( angle );
	this->x[5] = ::cos( angle );
}

void GLSLMatrix::rotateZ(const float angle)
{
	GLSLMatrix rotateMatrix;
	rotateMatrix.setRotateZ(angle);
	*(this) *= rotateMatrix;
}

void GLSLMatrix::setScale(const float x, const float y, const float z)
{
	this->x[0] = x;
	this->x[5] = y;
	this->x[10] = z;
}

void GLSLMatrix::multiple(const GLSLMatrix& rhs)
{
	float y[16];
	for( int i = 0; i < 4; ++ i ) {
		y[0+i] = x[0+i] * rhs.x[0] + x[4+i] * rhs.x[1] + x[8+i] * rhs.x[2] + x[12+i] * rhs.x[3];
		y[4+i] = x[0+i] * rhs.x[4] + x[4+i] * rhs.x[5] + x[8+i] * rhs.x[6] + x[12+i] * rhs.x[7];
		y[8+i] = x[0+i] * rhs.x[8] + x[4+i] * rhs.x[9] + x[8+i] * rhs.x[10] + x[12+i] * rhs.x[11];
		y[12+i] = x[0+i] * rhs.x[12] + x[4+i] * rhs.x[13] + x[8+i] * rhs.x[14] + x[12+i] * rhs.x[15];
	}
	for( int i = 0; i < 16; ++i ) {
		this->x[i] = y[i];
	}
}