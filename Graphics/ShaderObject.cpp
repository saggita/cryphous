#include "GLee.h"

#include "ShaderObject.h"
#include "TextureObject.h"
#include "GLSLMatrix.h"

#include <cassert>
#include <stdlib.h>

#include <string>
#include <iostream>
#include <fstream>

using namespace Crystal::Graphics;

ShaderObject::ShaderObject(void) :
	id( -1 )
{
}

ShaderObject::~ShaderObject(void)
{
	clear();
}

void ShaderObject::clear()
{
	release();
	if( id != -1 ) {
		glDeleteProgram( id );
	}
}

void ShaderObject::apply()
{
	glUseProgram( id );
}

void ShaderObject::release()
{
	glUseProgram( 0 );
}

void ShaderObject::build(const std::string& shaderName )
{
	clear();

	assert( glGetError() == GL_NO_ERROR );

	Shader vertexShader;
	Shader geometryShader;
	Shader fragmentShader;

	const std::string& vertexShaderFileName = "../Shaders/" + shaderName + ".vs";
	vertexShader.compileVertexShader( vertexShaderFileName );

	const std::string& fragmentShaderFileName = "../Shaders/" + shaderName + ".fs";
	fragmentShader.compileFragmentShader( fragmentShaderFileName );
	
	id = glCreateProgram();
	glAttachShader( id, vertexShader.getID() );
	glAttachShader( id, fragmentShader.getID() );
	
	GLint success;
	glLinkProgram( id );
	glGetProgramiv( id, GL_LINK_STATUS, &success );

	if ( !success ) {
		GLchar log[2048];
		glGetProgramInfoLog( id, 2048, NULL, log );
		fprintf( stderr, "Error in program #%d linkage!\n", this->id );
		fprintf( stderr, "Info log: %s\n", log );
		assert( false );
	}

	assert( glGetError() == GL_NO_ERROR );
}

bool ShaderObject::isValidUniform(const std::string& name, GLuint location) const
{
	if( location != -1 ) {
		return true;
	}
	std::cout << "uniform <" << name << "> not found." << std::endl;
	return false;
}

void ShaderObject::setUniform(const std::string& name, const int value)
{
	GLuint textureLoc = glGetUniformLocation( id, name.c_str() );
	assert( isValidUniform( name, textureLoc ) );
	glUniform1i( textureLoc, value );
}

void ShaderObject::setUniform( const std::string& name, const float value )
{
	const GLuint location = glGetUniformLocation( id, name.c_str() );
	assert( isValidUniform( name, location ) );
	glUniform1f( location, value );
}

void ShaderObject::setUniformVector( const std::string& name, const GLfloat* value)
{
	const GLuint location = glGetUniformLocation( id, name.c_str() );
	assert( isValidUniform( name, location ) );
	glUniform3fv( location, 1, value); 
}

void ShaderObject::setUniformMatrix( const std::string& name, const GLSLMatrix& matrix )
{
	const GLuint location = glGetUniformLocation( id, name.c_str() );
	assert( isValidUniform( name, location ) );
	glUniformMatrix4fv( location, 1, GL_FALSE, matrix.x );
}

void ShaderObject::setUniformTexture( const std::string& name, const TextureObject& textureObject) {
	const GLuint location = glGetUniformLocation( id, name.c_str() );
	assert( isValidUniform( name, location ) );
	glUniform1i( location, textureObject.getUnitID() );
}

void ShaderObject::setVertex( const std::string& name, std::vector<float>& vertices)
{
	if( vertices.empty() ) {
		return;
	}
	const GLuint location = glGetAttribLocation(id, name.c_str() );
	assert( isValidUniform( name, location ) );
	glVertexAttribPointer( location, 3, GL_FLOAT, GL_FALSE, 0, &(vertices.front()) );
	vertLocs.push_back( location );
}

void ShaderObject::setVertexAttrib(const char* name, std::vector<float>& attributes, const int size)
{
	if( attributes.empty() ) {
		return;
	}
	const GLuint location = glGetAttribLocation(id, name);
	assert( isValidUniform( name, location ) );
	glVertexAttribPointer( location, size, GL_FLOAT, GL_FALSE, 0, &(attributes.front()) );
	vertLocs.push_back( location );
}

void ShaderObject::drawPoints(const unsigned int howMany)
{
	enableVertexAttribArray();
	glDrawArrays( GL_POINTS, 0, howMany );
	disableVertexAttribArray();
}

void ShaderObject::drawQuads(const unsigned int howMany)
{
	enableVertexAttribArray();
	glDrawArrays( GL_QUADS, 0, howMany );
	disableVertexAttribArray();
}

void ShaderObject::drawTriangles(unsigned int howMany)
{
	enableVertexAttribArray();
	glDrawArrays( GL_TRIANGLES, 0, howMany );
	disableVertexAttribArray();
}

void ShaderObject::enableVertexAttribArray() const
{
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

void ShaderObject::bindFrag( const std::string& name )
{
	glBindFragDataLocation( id, 0, name.c_str() );
}
