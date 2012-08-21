#include "StdAfx.h"

#include "BillboardRenderer.h"
#include "BackGroundRenderer.h"

#include <cassert>
#include <boost/foreach.hpp>
#include <ctime>
#include <boost/random.hpp>

#include "GLSLUtility.h"

using namespace Crystal::Geom;
using namespace Crystal::Shader;
using namespace Crystal::Color;

BillboardRenderer::BillboardRenderer(const int width, const int height, const float& size, const float& alpha ) :
OffScreenRendererBase( width, height),
	size( size),
	alpha( alpha)
{
}

BillboardRenderer::~BillboardRenderer(void)
{
}

void BillboardRenderer::setVisualParticles(const VisualParticleList& visualParticles)
{
	positions.clear();
	colors.clear();
	float maxTemperature = 3000.0f;
	float minTemperature = 1000.0f;
	BOOST_FOREACH( const VisualParticle& vp, visualParticles ) {
		if( vp.temperature < minTemperature ) {
			continue;
		}
		const Vector3d& center = vp.center;
		const Vector3d& velocity = vp.velocity;
		const ColorRGBA<>& color = ColorAdaptor::get()->getColorFromCash( vp.temperature );
		positions.push_back( center.getX() );
		positions.push_back( center.getY() );
		positions.push_back( center.getZ() );
		colors.push_back( color.getRed());
		colors.push_back( color.getGreen());
		colors.push_back( color.getBlue());
		colors.push_back( (vp.temperature - minTemperature) / ( maxTemperature - minTemperature ) * alpha );
	}
}

void BillboardRenderer::onRender()
{
	glClearColor( 0.0, 0.0, 0.0, 0.0 );
	glClear( GL_COLOR_BUFFER_BIT );
	glEnable(GL_POINT_SPRITE);
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE); 
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	alphaTexture->apply( 0 );

	glClear( GL_DEPTH_BUFFER_BIT);	

	if( !positions.empty() ) {
		shaderObject.apply();
		shaderObject.setUniform("pointSize", size);
		shaderObject.setUniformMatrix("projectionMatrix", projectionMatrix);
		shaderObject.setUniformMatrix("modelviewMatrix", getModelviewMatrix());
		shaderObject.setUniformTexture("alphaTexture", *alphaTexture);
		shaderObject.setVertex( "position", positions ); 
		shaderObject.setVertexAttrib("color", colors, 4);
		shaderObject.bindFrag("fragColor");
		shaderObject.drawPoints( positions.size() / 3 );
		shaderObject.release();
	}

	alphaTexture->release();

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_POINT_SPRITE);
	glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
}

void BillboardRenderer::onInit()
{
	assert( GLSLUtility::hasNoError() );

	//glClearColor( 0.0, 0.0, 0.0, 1.0 );
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	projectionMatrix.setPerspectiveMatrix(-0.5f, 0.5f, 0.0f, 1.0f, 0.01f, 100.0f );
	
	shaderObject.createShader("Billboard");

	TextureCreator creator;
	creator.createTexture( 64, true );
	alphaTexture.reset( new TextureObject( 64, 64 ) );
	alphaTexture->initAlphaTexture( creator.getTexture(), 64, 64 );
}