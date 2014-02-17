#include "GLee.h"

#include "FrameBufferObject.h"
#include "RenderBufferObject.h"
#include "TextureObject.h"

#include <cassert>

using namespace Crystal::Graphics;

FrameBufferObject::FrameBufferObject(const int width, const int height ) :
renderBufferObject( new RenderBufferObject( width, height ) )
{
	init();
}

FrameBufferObject::~FrameBufferObject(void)
{
	GLuint ids[1] = { id };
	glDeleteFramebuffersEXT( 1, ids );
	delete renderBufferObject;
}

void FrameBufferObject::init()
{
	glGenFramebuffersEXT( 1, &id );
	glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, id );
	glFramebufferTexture2DEXT( GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, getTextureObject()->getID(), 0 );
	glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );
}

int FrameBufferObject::getWidth() const
{
	return renderBufferObject->getWidth();
}

int FrameBufferObject::getHeight() const
{
	return renderBufferObject->getHeight();
}

TextureObject* FrameBufferObject::getTextureObject()
{
	return renderBufferObject->getTextureObject();
}