#include "StdAfx.h"

#include "FluidRenderer.h"
#include "BillboardRenderer.h"
#include "CompositeRenderer.h"
#include "FrameBufferObject.h"

#include <boost/foreach.hpp>

#include <cassert>
#include <cmath>
#include <cstdlib>

using namespace Crystal::Geom;
using namespace Crystal::Shader;

FluidRenderer::FluidRenderer(const int width, const int height, const PBFRSetting& setting) :
FluidRendererBase( width, height, setting )
{
	billboardRenderer = new BillboardRenderer( getWidth(), getHeight(), setting.pointSize, setting.pointAlpha);
	compositeRenderer = new CompositeRenderer( getWidth(), getHeight() );
}

FluidRenderer::~FluidRenderer()
{
	delete compositeRenderer;
	delete billboardRenderer;
}

void FluidRenderer::onInit()
{
	openGLWrapper.SetCurrentRenderingContext();

	billboardRenderer->init();
	compositeRenderer->init();
	shaderObject.createShader("IntensityOffsetter");

	projectionMatrix.setOrthogonalMatrix( 0.0, 1.0, 0.0, 1.0, -1.0, 1.0 );
	
	points.resize(12);
	points[0] = 0.0; points[1] = 1.0; points[2] = 0.0;
	points[3] = 0.0; points[4] = 0.0; points[5] = 0.0;
	points[6] = 1.0; points[7] = 0.0; points[8] = 0.0;
	points[9] = 1.0; points[10] = 1.0; points[11] = 0.0;

	assert( GL_NO_ERROR == glGetError() );
}

void FluidRenderer::onRender()
{
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	assert( GL_NO_ERROR == glGetError() );

	billboardRenderer->setVisualParticles( *visualParticles );
	std::auto_ptr<FrameBufferObject> sourceBuffer( new FrameBufferObject( getWidth(), getHeight(), false) );
	billboardRenderer->render( *sourceBuffer );

	TextureObject& textureObject = sourceBuffer->getTextureObject();
	textureObject.apply(0);
	
	float colorOffset[3] = {0.0f, 0.0f, 0.0f};
	
	shaderObject.apply();
	shaderObject.setUniformMatrix("projectionMatrix", projectionMatrix);
	shaderObject.setUniformMatrix("modelviewMatrix", GLSLMatrix());
	shaderObject.setUniformTexture("offScreenTexture", textureObject);
	shaderObject.setUniformVector("colorOffset", colorOffset );
	shaderObject.setUniform("intensityScale", 1.0f);
	shaderObject.setVertex("position", points );
	shaderObject.drawQuads( 4);
	shaderObject.release();

	textureObject.release();
	//glFlush();
}