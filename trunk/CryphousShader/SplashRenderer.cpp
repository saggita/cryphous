#include "GLee.h"

#include "SplashRenderer.h"
#include "FrameBufferObject.h"

#include <cassert>
#include <ctime>

#include "GLSLUtility.h"

using namespace Cryphous::Geometry;
using namespace Cryphous::Shader;

SplashRenderer::SplashRenderer(const int width, const int height, float& size, float& alpha ) :
OffScreenRendererBase( width, height),
	size( size),
	alpha( alpha)
{
}

SplashRenderer::~SplashRenderer(void)
{
}

void SplashRenderer::setVisualParticles(const VisualParticleList& visualParticles)
{
	positions.clear();
	densities.clear();
	for( const VisualParticle& vp: visualParticles ) { 
		positions.push_back( vp.center.x );
		positions.push_back( vp.center.y );
		positions.push_back( vp.center.z );
		densities.push_back( vp.density );
	}
}

void SplashRenderer::onRender()
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
		shaderObject.setVertexAttrib("density", densities, 1 );
		shaderObject.bindFrag("fragColor");
		shaderObject.drawPoints( positions.size() / 3 );
		shaderObject.release();
	}

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_POINT_SPRITE);
	glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
}

void SplashRenderer::onInit()
{
	assert( GLSLUtility::hasNoError() );

	frameBufferObject = new FrameBufferObject(getWidth(), getHeight(), false);

	projectionMatrix.setPerspectiveMatrix(-0.5f, 0.5f, 0.0f, 1.0f, 0.01f, 100.0f );
	
	shaderObject.createShader("Splash");
}