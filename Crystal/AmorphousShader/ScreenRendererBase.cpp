#include "StdAfx.h"

#include "ScreenRendererBase.h"
#include "Camera.h"
#include "FrameBufferObject.h"

using namespace Crystal::Shader;

ScreenRendererBase::ScreenRendererBase(const int width, const int height) :
width( width),
height( height)
{
}

ScreenRendererBase::~ScreenRendererBase(void)
{
}

void ScreenRendererBase::init()
{
	assert( GL_NO_ERROR == glGetError() );
	onInit();
	assert( GL_NO_ERROR == glGetError() );
}

void ScreenRendererBase::render()
{
	assert( GL_NO_ERROR == glGetError() );
	glViewport( 0, 0, width , getHeight() );
	assert( GL_NO_ERROR == glGetError() );
	onRender();
}

void ScreenRendererBase::render(const FrameBufferObject& frameBufferObject)
{
	assert( GL_NO_ERROR == glGetError() );
	glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, frameBufferObject.getID() );
	glViewport( 0, 0, getWidth(), getHeight() );
	assert( GL_NO_ERROR == glGetError() );
	
	onRender();

	glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );
}

GLSLMatrix ScreenRendererBase::getModelviewMatrix()
{
	GLSLMatrix modelviewMatrix;
	Camera* camera = Camera::get();
	modelviewMatrix.translate( camera->cameraX, camera->cameraY, camera->zoom );
	modelviewMatrix.rotateX( camera->angleX );
	modelviewMatrix.rotateY( camera->angleY );
	modelviewMatrix.rotateZ( camera->angleZ );
	return modelviewMatrix;
}