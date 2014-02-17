#include "GLee.h"

#include "RenderBufferObject.h"

#include "TextureObject.h"

using namespace Crystal::Graphics;

RenderBufferObject::RenderBufferObject(const int width, const int height) :
textureObject( new TextureObject( width, height) )
{
	init();
}


RenderBufferObject::~RenderBufferObject(void)
{
	GLuint ids[1];
	ids[0] = this->id;
	glDeleteRenderbuffersEXT( 1, ids );
	delete textureObject;
}

void RenderBufferObject::init()
{
	glGenRenderbuffersEXT( 1, &this->id );
	glBindRenderbufferEXT( GL_RENDERBUFFER_EXT, this->id );
	glRenderbufferStorageEXT( GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, getWidth(), getHeight() );
}

int RenderBufferObject::getWidth() const
{
	return textureObject->getWidth();
}

int RenderBufferObject::getHeight() const
{
	return textureObject->getHeight();
}