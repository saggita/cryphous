#include "StdAfx.h"
#include "GLSLUtility.h"

#include <gl/glu.h>

#include <cstdio>
#include <cstdlib>
#include <cassert>

#include <vector>

#include <fstream>
#include <string>

using namespace Amorphous::Shader;

GLSLUtility::GLSLUtility(void)
{
}

GLSLUtility::~GLSLUtility(void)
{
}

const std::string GLSLUtility::LoadShaderText(const char *fileName)
{
	std::string shaderStr;
	std::ifstream stream(fileName, std::ios::in);
	std::string lineStr;
	while( std::getline(stream, lineStr) ) {
		shaderStr += lineStr + "\n";
	}
	shaderStr += "\0";
	return shaderStr;
}

void GLSLUtility::checkError()
{
	assert( GLEE_VERSION_2_0 );
	assert( GLEE_ARB_draw_buffers );
	assert( GLEE_ARB_vertex_shader );
	assert( GLEE_ARB_geometry_shader4 );
	assert( GLEE_ARB_fragment_shader );
	assert( GLEE_ARB_shader_objects );
	assert( GLEE_ARB_shading_language_100 );
	assert( GLEE_EXT_framebuffer_object);
	assert( GLEE_ARB_texture_float);
	assert( GLEE_ARB_texture_non_power_of_two );
}

bool GLSLUtility::hasNoError()
{
	GLenum error = glGetError();
	if( error != GL_NO_ERROR ) {
		const GLubyte* errorStr = gluErrorString( error );
		printf("%d, %s\n", error, errorStr );
		std::string eeErrorStr( GLeeGetErrorString() );
		printf("%s\n", eeErrorStr );
		return false;
	}
	return true;
}

bool GLSLUtility::hasNoShaderError(const unsigned int shader)
{
	GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	GLchar infoLog[2048];
	glGetShaderInfoLog(shader, 2048, NULL, infoLog );
	printf("%s\n", infoLog);
	assert( success != 0 );
	return success != 0;
}

