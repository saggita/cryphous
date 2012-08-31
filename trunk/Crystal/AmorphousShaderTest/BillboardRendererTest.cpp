#include "StdAfx.h"

#include "BillboardRendererTest.h"

#include <memory>
#include <algorithm>
#include <stdlib.h>

#include "../CrystalPhysics/PhysicsObjectFactory.h"

#include <boost/foreach.hpp>

using namespace Crystal::Geom;
using namespace Crystal::Shader;
using namespace Crystal::Physics;

BillboardRendererTest::BillboardRendererTest(const int width, const int height) :
OnScreenRendererBase( width, height),
renderer( width, height, setting )
{
}

BillboardRendererTest::~BillboardRendererTest(void)
{
}

void BillboardRendererTest::onRender()
{
	renderer.setup(&visualParticles);
	renderer.render();
}

void BillboardRendererTest::onIdle()
{
	simulation.simulate( &factory, ssetting );
	const ParticleVector& particles = factory.getOrderedParticles();
	for( int i = 0; i < particles.size(); ++i ) {
		visualParticles[i].center = particles[i]->center;
	}
	
	printf("visual particles = %d\n", visualParticles.size() ); 
}

void BillboardRendererTest::onInit()
{
	setting.pointSize = 10.0;

	std::vector<Vector3d> points;
	points.push_back( Vector3d(0.0, 0.0, 0.0 ) );
	points.push_back( Vector3d(0.0, 1.0, 0.0 ) );
	points.push_back( Vector3d(0.0, 2.0, 0.0 ) );
	PhysicsObjectCondition condition( points, 1000.0, 10000.0, 100.0, PhysicsObjectCondition::Fluid );

	SimulationSetting ssetting;
	factory.createPhysicsObject( condition, ssetting);
	
	visualParticles.resize(  300 );

	renderer.init();
}