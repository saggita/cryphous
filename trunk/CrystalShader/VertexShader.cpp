#include "GLee.h"

#include "VertexShader.h"

#include "GLSLUtility.h"

#include <cassert>
#include <stdlib.h>

#include <string>

using namespace Crystal::Shader;

VertexShader::VertexShader(void)
{
}

VertexShader::~VertexShader(void)
{
	glDeleteShader(id);
}

void VertexShader::createShader(const char* fullFileName)
{
    const GLchar *shStringPtr[1];
    const std::string& shString = GLSLUtility::LoadShaderText(fullFileName);
	
    this->id = glCreateShader(GL_VERTEX_SHADER);
    shStringPtr[0] = shString.c_str();
    glShaderSource(id, 1, shStringPtr, NULL);

    glCompileShader(this->id);
	assert( GLSLUtility::hasNoShaderError(this->id ) );
}