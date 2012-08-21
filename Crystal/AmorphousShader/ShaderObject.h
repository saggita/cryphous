#ifndef __SHADER_OBJECT_H__
#define __SHADER_OBJECT_H__

#include "VertexShader.h"
#include "GeometryShader.h"
#include "FragmentShader.h"

#include <vector>

namespace Crystal{
	namespace Shader{
		class GLSLMatrix;
		class TextureObject;

class ShaderObject
{
public:
	ShaderObject(void);

	~ShaderObject(void);

	void createShader(const char* shaderName);

	void apply();

	void release();

	void setUniform(const char* name, const int value);

	void setUniform(const char* name, const float value);

	void setUniformVector(const char* name, const GLfloat *value);

	void setUniformMatrix(const char* name, const GLSLMatrix& matrix);

	void setUniformTexture(const char* name, const TextureObject& textureObject);

	void setVertex(const char* name, std::vector<double>& vertices);

	void setVertexAttrib(const char* name, std::vector<double>& attributes, int size);

	void drawPoints(unsigned int howMany);

	void drawQuads(unsigned int howMany);

	void drawTriangles(unsigned int howMany);

	void bindFrag(const char* name);

private:
	unsigned int id;

	VertexShader vertexShader;
	GeometryShader geometryShader;
	FragmentShader fragmentShader;
	std::vector<unsigned int> vertLocs;

	void enableVertexAttribArray() const;

	void disableVertexAttribArray();

	bool isValidUniform(const std::string& name, GLuint location) const;
};

	}
}

#endif