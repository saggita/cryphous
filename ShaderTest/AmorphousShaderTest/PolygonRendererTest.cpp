#include "StdAfx.h"
#include "PolygonRendererTest.h"

using namespace Amorphous::Shader;

PolygonRendererTest::PolygonRendererTest(const int width, const int height) :
OnScreenRendererBase( width, height)
{
	polygonRenderer = new PolygonRenderer( getWidth(), getHeight(), "../PolygonModels/quad.obj");
}

PolygonRendererTest::~PolygonRendererTest(void)
{
	delete polygonRenderer;
}

void PolygonRendererTest::onRender()
{
	polygonRenderer->render( *frameBufferObject );

	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glEnable( GL_DEPTH_TEST );

	TextureObject& textureObject = frameBufferObject->getTextureObject();
	textureObject.apply( 0 );

	GLfloat colorOffset[3] = {0.0f, 0.0f, 0.0f};

	std::vector<double> points(12);
	points[0] = 0.0; points[1] = 1.0; points[2] = 0.0;
	points[3] = 0.0; points[4] = 0.0; points[5] = 0.0;
	points[6] = 1.0; points[7] = 0.0; points[8] = 0.0;
	points[9] = 1.0; points[10] = 1.0; points[11] = 0.0;
	
	shaderObject.apply();
	shaderObject.setUniformMatrix("projectionMatrix", projectionMatrix);
	shaderObject.setUniformMatrix("modelviewMatrix", GLSLMatrix());
	shaderObject.setUniformTexture("offScreenTexture", textureObject);
	shaderObject.setUniformVector("colorOffset", colorOffset);
	shaderObject.setUniform("intensityScale", 1.0f);
	shaderObject.setVertex("position", points );
	shaderObject.drawQuads( 4);
	shaderObject.release();

	textureObject.release();

	glDisable( GL_DEPTH_TEST );
}

void PolygonRendererTest::onInit()
{
	frameBufferObject.reset( new FrameBufferObject(getWidth(), getHeight(), false) );

	polygonRenderer->init();

	shaderObject.createShader("IntensityOffsetter");

	projectionMatrix.setOrthogonalMatrix( 0.0, 1.0, 0.0, 1.0, -1.0, 1.0 );
}