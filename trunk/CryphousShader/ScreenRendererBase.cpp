#include "GLee.h"

#include "ScreenRendererBase.h"
#include "Camera.h"

using namespace Cryphous::Shader;

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