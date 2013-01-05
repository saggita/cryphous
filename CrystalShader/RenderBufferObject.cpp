#include "GLee.h"

#include "RenderBufferObject.h"

#include "TextureObject.h"

using namespace Crystal::Shader;

RenderBufferObject::RenderBufferObject(const int width, const int height, const bool appendDepth) :
textureObject( new TextureObject( width, height) ),
depthTextureObject( 0 )
{
	init();
	if( appendDepth ) {
		depthTextureObject = new TextureObject( width, height );
		depthTextureObject->initDepthTexture( width, height );
	}
}


RenderBufferObject::~RenderBufferObject(void)
{
	GLuint ids[1];
	ids[0] = this->id;
	glDeleteRenderbuffersEXT( 1, ids );
	delete textureObject;
	delete depthTextureObject;
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