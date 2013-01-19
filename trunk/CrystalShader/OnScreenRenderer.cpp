#include "OnScreenRenderer.h"

#include "OffScreenRendererBase.h"
#include "FrameBufferObject.h"
#include "TextureObject.h"

#include <cassert>

using namespace Crystal::Shader;

OnScreenRenderer::OnScreenRenderer(const int width, const int height) :
ScreenRendererBase(width, height)
{
}

OnScreenRenderer::~OnScreenRenderer()
{
}

void OnScreenRenderer::render()
{
	assert( GL_NO_ERROR == glGetError() );
	glViewport( 0, 0, getWidth() , getHeight() );
	assert( GL_NO_ERROR == glGetError() );
	onRender();
}

void OnScreenRenderer::idle()
{
	onIdle();
}

void OnScreenRenderer::onInit()
{
	shaderObject.createShader("Quad");

	projectionMatrix.setOrthogonalMatrix( 0.0, 1.0, 0.0, 1.0, -1.0, 1.0 );
}

void OnScreenRenderer::onRender()
{
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glEnable( GL_DEPTH_TEST );

	TextureObject& textureObject = *texture;
	textureObject.apply( 0 );

	std::vector<double> points(12);
	points[0] = 0.0; points[1] = 1.0; points[2] = 0.0;
	points[3] = 0.0; points[4] = 0.0; points[5] = 0.0;
	points[6] = 1.0; points[7] = 0.0; points[8] = 0.0;
	points[9] = 1.0; points[10] = 1.0; points[11] = 0.0;
	
	shaderObject.apply();
	shaderObject.setUniformMatrix("projectionMatrix", projectionMatrix);
	shaderObject.setUniformMatrix("modelviewMatrix", GLSLMatrix());
	shaderObject.setUniformTexture("offScreenTexture", textureObject);
	shaderObject.setVertex("position", points );
	shaderObject.drawQuads( 4);
	shaderObject.release();

	textureObject.release();

	glDisable( GL_DEPTH_TEST );
}