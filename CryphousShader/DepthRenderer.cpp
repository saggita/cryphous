#include "GLee.h"

#include "DepthRenderer.h"

#include <cassert>
#include <ctime>

#include "GLSLUtility.h"

#include "FrameBufferObject.h"

using namespace Cryphous::Geometry;
using namespace Cryphous::Shader;

DepthRenderer::DepthRenderer(const int width, const int height, const float& size) :
OffScreenRendererBase( width, height),
	size( size)
{
}

DepthRenderer::~DepthRenderer(void)
{
}

void DepthRenderer::onRender()
{
	glClearColor( 0.0, 0.0, 0.0, 0.0 );
	glClear( GL_COLOR_BUFFER_BIT );
	glEnable(GL_POINT_SPRITE);
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE); 
	glEnable(GL_DEPTH_TEST);

	glClear( GL_DEPTH_BUFFER_BIT);	

	if( !collection->centers.empty() ) {
		shaderObject.apply();
		shaderObject.setUniform("pointSize", size);
		shaderObject.setUniformMatrix("projectionMatrix", projectionMatrix);
		shaderObject.setUniformMatrix("modelviewMatrix", getModelviewMatrix());
		shaderObject.setVertex( "position", collection->centers );
		shaderObject.setVertexAttrib( "density", collection->densities, 1 );
		shaderObject.bindFrag("fragColor");
		shaderObject.drawPoints( collection->centers.size() / 3 );
		shaderObject.release();
	}

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_POINT_SPRITE);
	glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
}

void DepthRenderer::onInit()
{
	assert( GLSLUtility::hasNoError() );

	frameBufferObject = new FrameBufferObject(getWidth(), getHeight(), false);

	projectionMatrix.setPerspectiveMatrix(-0.5f, 0.5f, 0.0f, 1.0f, 0.01f, 100.0f );
	
	shaderObject.createShader("Depth");
}