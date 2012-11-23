#include "StdAfx.h"

#include "OffScreenRendererBase.h"

#include "FrameBufferObject.h"

#include <cassert>

using namespace Amorphous::Shader;

OffScreenRendererBase::OffScreenRendererBase(const int width, const int height) :
ScreenRendererBase(width, height)
{
}

OffScreenRendererBase::~OffScreenRendererBase(void)
{
}

void OffScreenRendererBase::render(const FrameBufferObject& frameBufferObject)
{
	assert( GL_NO_ERROR == glGetError() );
	glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, frameBufferObject.getID() );
	glViewport( 0, 0, getWidth(), getHeight() );
	assert( GL_NO_ERROR == glGetError() );
	
	onRender();

	glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );
}