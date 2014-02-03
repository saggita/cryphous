#include "GLee.h"

#include "VertexShader.h"

#include "GLSLUtility.h"

#include <cassert>
#include <stdlib.h>

using namespace Crystal::Shader;

VertexShader::VertexShader(void)
{
}

VertexShader::~VertexShader(void)
{
	glDeleteShader(id);
}

void VertexShader::createShader(const std::string& fileName)
{
    const GLchar *shStringPtr[1];
    const std::string& shString = GLSLUtility::LoadShaderText(fileName.c_str());
	
    this->id = glCreateShader(GL_VERTEX_SHADER);
    shStringPtr[0] = shString.c_str();
    glShaderSource(id, 1, shStringPtr, NULL);

    glCompileShader(this->id);
	assert( GLSLUtility::hasNoShaderError(this->id ) );
}