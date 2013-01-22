#include "GLee.h"

#include "PointSpriteRenderer.h"
#include "FrameBufferObject.h"
//#include "BackGroundRenderer.h"

#include <cassert>
#include <ctime>

#include "GLSLUtility.h"

using namespace Crystal::Geom;
using namespace Crystal::Shader;

PointSpriteRenderer::PointSpriteRenderer(const int width, const int height, float& size, float& alpha ) :
OffScreenRendererBase( width, height),
	size( size),
	alpha( alpha)
{
}

PointSpriteRenderer::~PointSpriteRenderer(void)
{
}

void PointSpriteRenderer::setVisualParticles(const VisualParticleList& visualParticles)
{
	positions.clear();
	colors.clear();
	for( VisualParticleList::const_iterator iter = visualParticles.begin(); iter != visualParticles.end(); ++iter ) {
		const VisualParticle& vp = *iter;
		const Vector3d& center = vp.center;
		positions.push_back( center.x );
		positions.push_back( center.y );
		positions.push_back( center.z );
		colors.push_back( 0.5f);
		colors.push_back( 0.5f);
		colors.push_back( 0.9f);
		colors.push_back( 0.1f );
	}
}

void PointSpriteRenderer::onRender()
{
	glClearColor( 0.8f, 0.8f, 0.9f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
	glEnable(GL_POINT_SPRITE);
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE); 
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	glClear( GL_DEPTH_BUFFER_BIT);	

	if( !positions.empty() ) {
		shaderObject.apply();
		shaderObject.setUniform("pointSize", size);
		shaderObject.setUniformMatrix("projectionMatrix", projectionMatrix);
		shaderObject.setUniformMatrix("modelviewMatrix", getModelviewMatrix());
		shaderObject.setVertex( "position", positions ); 
		shaderObject.setVertexAttrib("color", colors, 4);
		shaderObject.bindFrag("fragColor");
		shaderObject.drawPoints( positions.size() / 3 );
		shaderObject.release();
	}


	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_POINT_SPRITE);
	glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
}

void PointSpriteRenderer::onInit()
{
	assert( GLSLUtility::hasNoError() );

	frameBufferObject = new FrameBufferObject(getWidth(), getHeight(), false);

	projectionMatrix.setPerspectiveMatrix(-0.5f, 0.5f, 0.0f, 1.0f, 0.01f, 100.0f );
	
	shaderObject.createShader("PointSprite");
}