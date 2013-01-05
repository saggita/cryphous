
#include "OffScreenRendererBase.h"

#include "FrameBufferObject.h"

#include <cassert>

using namespace Crystal::Shader;

OffScreenRendererBase::OffScreenRendererBase(const int width, const int height) :
ScreenRendererBase(width, height),
offScreenRenderer(0)
{
}

OffScreenRendererBase::~OffScreenRendererBase(void)
{
	delete offScreenRenderer;
}

void OffScreenRendererBase::render(const FrameBufferObject& frameBufferObject)
{
	renderOffScreen();

	assert( GL_NO_ERROR == glGetError() );
	glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, frameBufferObject.getID() );
	glViewport( 0, 0, getWidth(), getHeight() );
	assert( GL_NO_ERROR == glGetError() );

	onRender();

	glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );
}

void OffScreenRendererBase::renderOffScreen()
{
	if( offScreenRenderer ) {
		offScreenRenderer->render( *frameBufferObject );
	}
}