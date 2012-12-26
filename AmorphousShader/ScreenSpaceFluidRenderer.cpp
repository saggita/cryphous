#include "ScreenSpaceFluidRenderer.h"

#include "DepthRenderer.h"
#include "FrameBufferObject.h"
#include "TextureObject.h"

#include <cassert>

using namespace Amorphous::Shader;

ScreenSpaceFluidRenderer::ScreenSpaceFluidRenderer(const int width, const int height) :
OffScreenRendererBase(width, height)
{
}

ScreenSpaceFluidRenderer::~ScreenSpaceFluidRenderer()
{
	delete offScreenRenderer;
}

void ScreenSpaceFluidRenderer::onInit()
{
	frameBufferObject = new FrameBufferObject(getWidth(), getHeight(), false);

	offScreenRenderer->init();

	shaderObject.createShader("ScreenSpaceFluid");

	projectionMatrix.setOrthogonalMatrix( 0.0, 1.0, 0.0, 1.0, -1.0, 1.0 );
}

void ScreenSpaceFluidRenderer::renderOffScreen()
{
	offScreenRenderer->render( *frameBufferObject );
}

void ScreenSpaceFluidRenderer::onRender()
{
	glClear( GL_DEPTH_BUFFER_BIT);	

	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glDisable( GL_DEPTH_TEST );

	TextureObject& textureObject = frameBufferObject->getTextureObject();
	textureObject.apply( 0 );

	std::vector<double> points(12);
	points[0] = 0.0; points[1] = 1.0; points[2] = 0.0;
	points[3] = 0.0; points[4] = 0.0; points[5] = 0.0;
	points[6] = 1.0; points[7] = 0.0; points[8] = 0.0;
	points[9] = 1.0; points[10] = 1.0; points[11] = 0.0;
	
	shaderObject.apply();
	shaderObject.setUniformMatrix("projectionMatrix", projectionMatrix);
	shaderObject.setUniformMatrix("modelviewMatrix", GLSLMatrix());
	shaderObject.setUniform("near", 0.01f);
	shaderObject.setUniform("far", 100.0f);
	shaderObject.setUniformTexture("depthTexture", textureObject);
	shaderObject.setVertex("position", points );
	shaderObject.bindFrag("fragColor");
	shaderObject.drawQuads( 4);
	shaderObject.release();

	textureObject.release();

	glEnable( GL_DEPTH_TEST );
}