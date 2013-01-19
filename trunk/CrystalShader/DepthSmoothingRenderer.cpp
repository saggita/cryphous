#include "DepthSmoothingRenderer.h"

#include "DepthRenderer.h"
#include "FrameBufferObject.h"
#include "TextureObject.h"

#include <cassert>

using namespace Crystal::Shader;

DepthSmoothingRenderer::DepthSmoothingRenderer(const int width, const int height) :
OffScreenRendererBase(width, height)
{
}

DepthSmoothingRenderer::~DepthSmoothingRenderer()
{
}

void DepthSmoothingRenderer::onInit()
{
	frameBufferObject = new FrameBufferObject(getWidth(), getHeight(), false);

	shaderObject.createShader("DepthSmoothing");

	projectionMatrix.setOrthogonalMatrix( 0.0, 1.0, 0.0, 1.0, -1.0, 1.0 );
}

void DepthSmoothingRenderer::onRender()
{
	glClear( GL_DEPTH_BUFFER_BIT);	

	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glDisable( GL_DEPTH_TEST );

	TextureObject& textureObject = *depthTexture;
	textureObject.apply( 0 );

	std::vector<double> points(12);
	points[0] = 0.0; points[1] = 1.0; points[2] = 0.0;
	points[3] = 0.0; points[4] = 0.0; points[5] = 0.0;
	points[6] = 1.0; points[7] = 0.0; points[8] = 0.0;
	points[9] = 1.0; points[10] = 1.0; points[11] = 0.0;
	
	shaderObject.apply();
	shaderObject.setUniformMatrix("projectionMatrix", projectionMatrix);
	shaderObject.setUniformMatrix("modelviewMatrix", GLSLMatrix());
	shaderObject.setUniformTexture("depthTexture", textureObject);
	shaderObject.setVertex("position", points );
	shaderObject.bindFrag("fragColor");
	shaderObject.drawQuads( 4);
	shaderObject.release();

	textureObject.release();

	glEnable( GL_DEPTH_TEST );
}