#include "StdAfx.h"
#include "TextureObject.h"

using namespace Crystal::Shader;

TextureObject::TextureObject(const int width, const int height) :
unitID(0)
{
	init( width, height );
}

TextureObject::TextureObject(const std::vector<GLubyte>& pixels, const int width, const int height) :
unitID(0)
{
	init( pixels, width, height );
}

TextureObject::TextureObject(const std::vector<GLfloat>& pixels, const int width, const int height) :
unitID(0)
{
	init( pixels, width, height );
}

TextureObject::~TextureObject(void)
{
	GLuint ids[1] = {this->id};
	glDeleteTextures(1, ids );
}

void TextureObject::init( const int width, const int height )
{
	type = RGBATexture;
	this->width = width;
	this->height = height;
	glEnable(GL_TEXTURE_2D);
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
    glGenTextures( 1, &this->id );
    glBindTexture( GL_TEXTURE_2D, this->id );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
	glDisable(GL_TEXTURE_2D);
}

void TextureObject::initAlphaTexture(const std::vector<GLubyte>& alphas, const int width, const int height)
{
	type = AlphaTexture;
	glEnable(GL_TEXTURE_2D);
	glTexImage2D( GL_TEXTURE_2D, 0, GL_ALPHA, width, height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, &(alphas.front()) );
	glDisable(GL_TEXTURE_2D);
}

void TextureObject::initDepthTexture(const int width, const int height)
{
	type = DepthTexture;
	glEnable(GL_TEXTURE_2D);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
	glDisable(GL_TEXTURE_2D);
}

void TextureObject::init(const std::vector<GLubyte>& pixels, const int width, const int height)
{
	type = RGBATexture;
	init( width, height );
	glEnable(GL_TEXTURE_2D);
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(pixels.front()) );
	glDisable(GL_TEXTURE_2D);
}

void TextureObject::init(const std::vector<GLfloat>& pixels, const int width, const int height)
{
	type = RGBATexture;
	init( width, height );
	glEnable(GL_TEXTURE_2D);
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_FLOAT, &(pixels.front()) );
	glDisable(GL_TEXTURE_2D);
}

void TextureObject::apply(const unsigned int unitID)
{
	this->unitID = unitID;
	glActiveTexture( GL_TEXTURE0 + unitID );
	glBindTexture(GL_TEXTURE_2D, this->id );
	glEnable(GL_TEXTURE_2D);
}

void TextureObject::release()
{
	glBindTexture(GL_TEXTURE_2D, 0 );
	glDisable(GL_TEXTURE_2D);
}