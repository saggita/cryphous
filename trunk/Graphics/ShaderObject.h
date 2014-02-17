#ifndef __CRYSTAL_GRAPHICS_SHADER_OBJECT_H__
#define __CRYSTAL_GRAPHICS_SHADER_OBJECT_H__

#include "GLee.h"

#include <vector>


#include <string>

#include "Shader.h"

namespace Crystal{
	namespace Graphics {
		class GLSLMatrix;
		class TextureObject;

class ShaderObject
{
public:
	ShaderObject(void);

	~ShaderObject(void);

	void clear();

	void build( const std::string& shaderName );

	void apply();

	void release();

	void setUniform( const std::string& name, const int value );

	void setUniform( const std::string& name, const float value );

	void setUniformVector( const std::string& name, const GLfloat *value );

	void setUniformMatrix( const std::string& name, const GLSLMatrix& matrix );

	void setUniformTexture( const std::string& name, const TextureObject& textureObject );

	void setVertex( const std::string& name, std::vector<float>& vertices );

	void setVertexAttrib( const char* name, std::vector<float>& attributes, int size );

	void drawPoints( unsigned int howMany );

	void drawQuads( unsigned int howMany );

	void drawTriangles(unsigned int howMany);

	void bindFrag( const std::string& name );

private:
	unsigned int id;

	std::vector<unsigned int> vertLocs;

	void enableVertexAttribArray() const;

	void disableVertexAttribArray();

	bool isValidUniform(const std::string& name, GLuint location) const;
};

	}
}

#endif