#include "StdAfx.h"

#include "ShaderObject.h"
#include "TextureObject.h"
#include "GLSLMatrix.h"

#include "GLSLUtility.h"

#include <cassert>
#include <stdlib.h>

#include <string>
#include <iostream>

using namespace Amorphous::Shader;

ShaderObject::ShaderObject(void)
{
}

ShaderObject::~ShaderObject(void)
{
	glDeleteProgram( id);
}

void ShaderObject::apply()
{
	glUseProgram( id);
}

void ShaderObject::release()
{
	glUseProgram( 0);
}

void ShaderObject::createShader(const char* shaderName)
{
	assert( GLSLUtility::hasNoError() );

	std::string fragmentShaderFileName = "../Shaders/";
	fragmentShaderFileName += shaderName;
	fragmentShaderFileName += ".fs";
	fragmentShader.createShader( fragmentShaderFileName.c_str() );
	
	std::string vertexShaderFileName = "../Shaders/";
	vertexShaderFileName += shaderName;
	vertexShaderFileName += ".vs";
	vertexShader.createShader( vertexShaderFileName.c_str() );
	
	std::string geometryShaderFileName = "../Shaders/";
	geometryShaderFileName += shaderName;
	geometryShaderFileName += ".gs";
	geometryShader.createShader( geometryShaderFileName.c_str() );

	this->id = glCreateProgram();
	glAttachShader(this->id, vertexShader.getID());
	glAttachShader(this->id, fragmentShader.getID());
	glAttachShader(this->id, geometryShader.getID());
	
	GLint success;
    glLinkProgram(this->id);
    glGetProgramiv(this->id, GL_LINK_STATUS, &success);

	if (!success) {
        GLchar infoLog[2048];
        glGetProgramInfoLog(this->id, 2048, NULL, infoLog);
        fprintf(stderr, "Error in program #%d linkage!\n", this->id);
        fprintf(stderr, "Info log: %s\n", infoLog);
        assert( false );
    }

	assert( GLSLUtility::hasNoError() );
}

bool ShaderObject::isValidUniform(const std::string& name, GLuint location) const
{
	if( location != -1 ) {
		return true;
	}
	std::cout << "uniform <" << name << "> not found." << std::endl;
	return false;
}

void ShaderObject::setUniform(const char *name, const int value)
{
	GLuint textureLoc = glGetUniformLocation(this->id, name);
	assert( isValidUniform( name, textureLoc ) );
	glUniform1i( textureLoc, value );
}

void ShaderObject::setUniform(const char* name, const float value)
{
	GLuint textureLoc = glGetUniformLocation(this->id, name);
	assert( isValidUniform( name, textureLoc ) );
	glUniform1f( textureLoc, value );
}

void ShaderObject::setUniformVector(const char* name, const GLfloat *value)
{
	GLuint loc = glGetUniformLocation(id, name);
	assert( isValidUniform( name, loc ) );
	glUniform3fv( loc, 1, value); 
}

void ShaderObject::setUniformMatrix(const char* name, const GLSLMatrix& matrix)
{
	const GLuint uniformLoc = glGetUniformLocation(this->id, name);
	assert( isValidUniform( name, uniformLoc ) );
	glUniformMatrix4fv( uniformLoc, 1, GL_FALSE, matrix.x );
}

void ShaderObject::setUniformTexture(const char* name, const TextureObject& textureObject) {
	const GLuint uniformLoc = glGetUniformLocation(id, name);
	assert( isValidUniform( name, uniformLoc ) );
	glUniform1i( uniformLoc, textureObject.getUnitID() );
}

void ShaderObject::setVertex(const char* name, std::vector<double>& vertices)
{
	const GLuint vertLoc = glGetAttribLocation(id, name);
	assert( isValidUniform( name, vertLoc ) );
	glVertexAttribPointer( vertLoc, 3, GL_DOUBLE, GL_FALSE, 0, &(vertices.front()) );
	vertLocs.push_back( vertLoc );
}

void ShaderObject::setVertexAttrib(const char* name, std::vector<double>& attributes, const int size)
{
	const GLuint loc = glGetAttribLocation(id, name);
	assert( isValidUniform( name, loc ) );
	glVertexAttribPointer( loc, size, GL_DOUBLE, GL_FALSE, 0, &(attributes.front()) );
	vertLocs.push_back( loc );
}

void ShaderObject::drawPoints(const unsigned int howMany)
{
	enableVertexAttribArray();
	glDrawArrays(GL_POINTS, 0, howMany);
	disableVertexAttribArray();
}

void ShaderObject::drawQuads(const unsigned int howMany)
{
	enableVertexAttribArray();
	glDrawArrays(GL_QUADS, 0, howMany);
	disableVertexAttribArray();
}

void ShaderObject::drawTriangles(unsigned int howMany)
{
	enableVertexAttribArray();
	glDrawArrays(GL_TRIANGLES, 0, howMany);
	disableVertexAttribArray();
}

void ShaderObject::enableVertexAttribArray() const
{
	assert( !vertLocs.empty() );
	for( size_t i = 0; i < vertLocs.size(); ++i ) {
		assert( vertLocs[i] != -1 );
		glEnableVertexAttribArray( vertLocs[i] );
	}
}

void ShaderObject::disableVertexAttribArray()
{
	for( size_t i = 0; i < vertLocs.size(); ++i ) {
		glDisableVertexAttribArray( vertLocs[i] );
	}
	vertLocs.clear();
}

void ShaderObject::bindFrag(const char* name) {
	glBindFragDataLocation( id, 0, name);
}
