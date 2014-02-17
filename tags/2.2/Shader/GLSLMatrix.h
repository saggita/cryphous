#ifndef __GLSL_MATRIX_H__
#define __GLSL_MATRIX_H__

#include "../Math/Matrix3d.h"

namespace Crystal{
	namespace Shader{

class GLSLMatrix
{
public:
	GLSLMatrix(void);

	~GLSLMatrix(void);

	void setIdentityMatrix();

	void setOrthogonalMatrix(const float left, const float right, const float bottom, const float top, const float nearZ, const float farZ);

	void setPerspectiveMatrix(const float left, const float right, const float bottom, const float top, const float nearZ, const float farZ);

	void rotateX(const float angle);

	void rotateY(const float angle);

	void rotateZ(const float angle);

	void translate(const float x, const float y, const float z);

	void setScale(const float x, const float y, const float z);

	void multiple(const GLSLMatrix& rhs);

	void operator*=(const GLSLMatrix& rhs) { multiple(rhs); }

	float x[16];

	static GLSLMatrix IdentityMatrix() {
		GLSLMatrix matrix;
		matrix.setIdentityMatrix();
		return matrix;
	}

private:
	void setRotateX(const float angle);

	void setRotateY(const float angle);

	void setRotateZ(const float angle);

	void setTranslate(const float x, const float y, const float z);
};

	}
}

#endif