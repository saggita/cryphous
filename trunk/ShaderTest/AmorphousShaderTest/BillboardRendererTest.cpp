#include "StdAfx.h"

#include "BillboardRendererTest.h"

#include <memory>
#include <algorithm>
#include <stdlib.h>

#include <boost/foreach.hpp>

using namespace Amorphous::Geom;
using namespace Amorphous::Color;
using namespace Amorphous::Shader;

BillboardRendererTest::BillboardRendererTest(const int width, const int height, const std::vector<Amorphous::Shader::PolygonModel>& solidModels) :
OnScreenRendererBase( width, height),
renderer( width, height, setting ),
solidModels( solidModels)
{
}

BillboardRendererTest::~BillboardRendererTest(void)
{
}

void BillboardRendererTest::onRender()
{
	renderer.setup(&visualParticles, &solidModels);
	renderer.render();
}

bool isUnderTemperature(const VisualParticle& vp)
{
	return vp.temperature < 1500.0;
}

void BillboardRendererTest::onIdle()
{
	BOOST_FOREACH( VisualParticle& vp, visualParticles ) {
		vp.center += vp.velocity * 0.1;
		vp.velocity *= 0.98;
		vp.temperature *= 0.99;
	}

	for( int i = 0; i < 300; ++ i ) {
		const Vector3d<> center( 0.0f, 0.0f, 0.0f );
		const Vector3d<> velocity( rand() % 500 / 1000.0f - 0.25f, rand() % 900 / 1000.0f + 0.1f, rand() % 500 / 1000.0f -0.25f );
		const double temperature = rand() % 100 / 1.0f + 2500.0f;
		visualParticles.push_back( VisualParticle( center, temperature, 0.1, velocity ) );
	}
	
	visualParticles.erase( std::remove_if( visualParticles.begin(), visualParticles.end(), isUnderTemperature ), visualParticles.end() );
	printf("visual particles = %d\n", visualParticles.size() ); 
}

void BillboardRendererTest::onInit()
{
	renderer.init();
}