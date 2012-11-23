#include "StdAfx.h"
#include "CompositeRenderer.h"
#include "TextureObject.h"
#include <cassert>

using namespace Amorphous::Shader;

CompositeRenderer::CompositeRenderer(const int width, const int height) :
OffScreenRendererBase( width, height),
texture0( 0),
texture1( 0)
{
}

CompositeRenderer::CompositeRenderer(TextureObject* texture0, TextureObject* texture1 ):
OffScreenRendererBase( texture0->getWidth(), texture0->getHeight() ),
texture0( texture0), texture1( texture1)
{
	assert( texture0->getWidth() == texture1->getWidth() );
	assert( texture0->getHeight() == texture1->getHeight() );
}

void CompositeRenderer::setTextureObject(TextureObject* texture0,TextureObject* texture1 )
{
	this->texture0 = texture0;
	this->texture1 = texture1;
}

void CompositeRenderer::onRender()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	texture0->apply(0);
	texture1->apply(1);

	projectionMatrix.setOrthogonalMatrix( 0.0, 1.0, 0.0, 1.0, -1.0, 1.0 );
		
	std::vector<double> points(12);
	points[0] = 0.0; points[1] = 1.0; points[2] = 0.0;
	points[3] = 0.0; points[4] = 0.0; points[5] = 0.0;
	points[6] = 1.0; points[7] = 0.0; points[8] = 0.0;
	points[9] = 1.0; points[10] = 1.0; points[11] = 0.0;
	
	shaderObject.apply();
	shaderObject.setUniformMatrix("projectionMatrix", projectionMatrix);
	shaderObject.setUniformMatrix("modelviewMatrix", GLSLMatrix());
	shaderObject.setUniformTexture("offScreenTexture0", *texture0);
	shaderObject.setUniformTexture("offScreenTexture1", *texture1);
	shaderObject.setVertex("position", points );
	shaderObject.drawQuads( 4);

	shaderObject.release();

	texture0->release();
	texture1->release();
}

void CompositeRenderer::onInit()
{
	shaderObject.createShader("Compositor");
}