#include "FragmentShader.h"

#include "GLee.h"


#include "GLSLUtility.h"

#include <cassert>
#include <stdlib.h>

#include <string>

using namespace Amorphous::Shader;

FragmentShader::FragmentShader(void)
{
}

FragmentShader::~FragmentShader(void)
{
	glDeleteShader(id);
}

void FragmentShader::createShader(const char* fullFileName)
{
    const GLchar *shStringPtr[1];
    const std::string shString = GLSLUtility::LoadShaderText(fullFileName);
	
	this->id = glCreateShader(GL_FRAGMENT_SHADER);
    shStringPtr[0] = shString.c_str();
    glShaderSource(id, 1, shStringPtr, NULL);

    glCompileShader(this->id);
	assert( GLSLUtility::hasNoShaderError(this->id ) );
}