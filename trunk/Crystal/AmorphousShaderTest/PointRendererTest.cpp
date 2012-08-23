#include "StdAfx.h"

#include "PointRendererTest.h"

#include <memory>
#include <algorithm>
#include <stdlib.h>

#include <boost/foreach.hpp>

using namespace Crystal::Geom;
using namespace Crystal::Color;
using namespace Crystal::Shader;

PointRendererTest::PointRendererTest(const int width, const int height, std::vector<Crystal::Shader::PolygonModel>& solidModels) :
OnScreenRendererBase( width, height),
renderer( width, height, setting ),
solidModels( solidModels)
{
}

PointRendererTest::~PointRendererTest(void)
{
}

void PointRendererTest::onRender()
{
	renderer.setup(&visualParticles, &solidModels);
	renderer.render();
}

bool isUnderThreshold(const VisualParticle& vp)
{
	return vp.temperature < 1500.0;
}

void PointRendererTest::onIdle()
{
	BOOST_FOREACH( VisualParticle& vp, visualParticles ) {
		vp.center += vp.velocity * 0.1f;
		vp.velocity *= 0.98f;
		vp.temperature *= 0.99f;
	}

	for( int i = 0; i < 300; ++ i ) {
		const Vector3d center( 0.0f, 0.0f, 0.0f );
		const Vector3d velocity( rand() % 500 / 1000.0f - 0.25f, rand() % 900 / 1000.0f + 0.1f, rand() % 500 / 1000.0f -0.25f );
		const double temperature = rand() % 100 / 1.0f + 2500.0f;
		visualParticles.push_back( VisualParticle( center, temperature, 0.1, velocity ) );
	}
	
	visualParticles.erase( std::remove_if( visualParticles.begin(), visualParticles.end(), isUnderThreshold ), visualParticles.end() );
	printf("visual particles = %d\n", visualParticles.size() ); 
}

void PointRendererTest::onInit()
{
	setting.blurRatio = 0.0f;
	renderer.init();
}