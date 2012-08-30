#include "StdAfx.h"

#include "BillboardRendererTest.h"

#include <memory>
#include <algorithm>
#include <stdlib.h>

#include <boost/foreach.hpp>

using namespace Crystal::Geom;
using namespace Crystal::Shader;

BillboardRendererTest::BillboardRendererTest(const int width, const int height, const std::vector<Crystal::Shader::PolygonModel>& solidModels) :
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

void BillboardRendererTest::onIdle()
{
	BOOST_FOREACH( VisualParticle& vp, visualParticles ) {
		vp.center += vp.velocity * 0.1f;
		vp.velocity *= 0.98f;
	}
	visualParticles.resize(300);

	for( int i = 0; i < 300; ++ i ) {
		const Vector3d center( 0.0f, 0.0f, 0.0f );
		const Vector3d velocity( rand() % 500 / 1000.0f - 0.25f, rand() % 900 / 1000.0f + 0.1f, rand() % 500 / 1000.0f -0.25f );
		const double temperature = rand() % 100 / 1.0f + 2500.0f;
		visualParticles[i] = VisualParticle( center, 0.1, velocity );
	}
	
	printf("visual particles = %d\n", visualParticles.size() ); 
}

void BillboardRendererTest::onInit()
{
	setting.repeatLevel = 10;
	renderer.init();
}