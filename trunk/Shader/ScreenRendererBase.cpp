#include "GLee.h"

#include "ScreenRendererBase.h"
#include "Camera.h"

using namespace Crystal::Shader;

ScreenRendererBase::ScreenRendererBase()
{
}

ScreenRendererBase::~ScreenRendererBase(void)
{
}

void ScreenRendererBase::init()
{
	onInit();
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