#include "GLee.h"
#include "Shader.h"

#include <string>
#include <fstream>
#include <cassert>

using namespace Crystal::Graphics;

Shader::Shader(void) :
	id( -1 )
{
}

Shader::~Shader(void)
{
	clear();
}

void Shader::clear()
{
	if( id != -1 ) {
		glDeleteShader( id );
	}
}

void valid(const unsigned int id)
{
	GLint success;
	glGetShaderiv( id, GL_COMPILE_STATUS, &success);
	GLchar infoLog[2048];
	glGetShaderInfoLog( id, 2048, NULL, infoLog );
	printf("%s\n", infoLog);
	assert( success != 0 );
}

std::string loadShaderText( const std::string& fileName )
{
	std::string str;
	std::ifstream stream( fileName, std::ios::in );
	std::string lineStr;
	while( std::getline(stream, lineStr) ) {
		str += lineStr + "\n";
	}
	str += "\0";
	return str;
}

void compile( const std::string& source, int id )
{
	const GLchar *strPtr[1];
	strPtr[0] = source.c_str();
	glShaderSource( id, 1, strPtr, NULL );

	glCompileShader( id );
	valid( id );

	assert( glGetError() == GL_NO_ERROR );
}

void Shader::compileVertexShader( const std::string& fileName )
{
	clear();
	id = glCreateShader( GL_VERTEX_SHADER );
	const std::string& source = loadShaderText( fileName );
	compile( source, id );
}

void Shader::compileFragmentShader( const std::string& fileName )
{
	clear();
	id = glCreateShader( GL_FRAGMENT_SHADER );
	const std::string& source = loadShaderText( fileName );
	compile( source, id );
}