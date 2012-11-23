//#include "GLee.h"
#include "StdAfx.h"
#include "GLSLUtility.h"

#include "FrameBufferObject.h"
#include "RenderBufferObject.h"
#include "TextureObject.h"

#include <cassert>

using namespace Amorphous::Shader;

FrameBufferObject::FrameBufferObject(const int width, const int height, const bool appendDepth) :
renderBufferObject( new RenderBufferObject( width, height, appendDepth) ),
appendDepth( appendDepth)
{
	init();
}

FrameBufferObject::~FrameBufferObject(void)
{
	GLuint ids[1];
	ids[0] = this->id;
	glDeleteFramebuffersEXT( 1, ids );
	delete renderBufferObject;
}

void FrameBufferObject::init()
{
	glGenFramebuffersEXT( 1, &this->id );
	glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, this->id );

	glFramebufferTexture2DEXT( GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, getTextureObject().getID(), 0 );
	if( appendDepth ) {
		glFramebufferTexture2DEXT( GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, getDepthTextureObject().getID(), 0 );
	}

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

TextureObject& FrameBufferObject::getTextureObject()
{
	return renderBufferObject->getTextureObject();
}

TextureObject& FrameBufferObject::getDepthTextureObject()
{
	assert( appendDepth );
	return renderBufferObject->getDepthTextureObject();
}