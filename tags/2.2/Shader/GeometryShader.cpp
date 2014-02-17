#include "GeometryShader.h"

#include "GLee.h"

#include "GLSLUtility.h"

#include <cassert>
#include <stdlib.h>
#include <string>

using namespace Crystal::Shader;

GeometryShader::GeometryShader(void)
{
}

GeometryShader::~GeometryShader(void)
{
	glDeleteShader(id);
}

void GeometryShader::createShader(const std::string& fileName)
{
    const GLchar *shStringPtr[1];

    const std::string shString = GLSLUtility::LoadShaderText(fileName.c_str());
	
	this->id = glCreateShader(GL_GEOMETRY_SHADER_ARB);
    shStringPtr[0] = shString.c_str();
    glShaderSource(id, 1, shStringPtr, NULL);

    glCompileShader(this->id);
	assert( GLSLUtility::hasNoShaderError(this->id ) );
}