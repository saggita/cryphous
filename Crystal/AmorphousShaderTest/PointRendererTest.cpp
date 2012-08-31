#include "StdAfx.h"

#include "PointRendererTest.h"

#include <memory>
#include <algorithm>
#include <stdlib.h>

#include <boost/foreach.hpp>

using namespace Crystal::Geom;
using namespace Crystal::Physics;
using namespace Crystal::Shader;

PointRendererTest::PointRendererTest(const int width, const int height) :
OnScreenRendererBase( width, height),
renderer( width, height, setting )
{
}

PointRendererTest::~PointRendererTest(void)
{
}

void PointRendererTest::onRender()
{
	renderer.setup(&visualParticles);
	renderer.render();
}

void PointRendererTest::onIdle()
{
	simulation.simulate( &factory, ssetting );
	Particle* particle = factory.getOrderedParticles().front();
	visualParticles.front().center = Vector3d( 0.0, 0.0, 0.0 );//particle->center;
	
	printf("visual particles = %d\n", visualParticles.size() ); 
}

void PointRendererTest::onInit()
{
	std::vector<Vector3d> points;
	points.push_back( Vector3d(0.0, 0.0, 0.0 ) );
	PhysicsObjectCondition condition( points, 1000.0, 10000.0, 100.0, PhysicsObjectCondition::Fluid );

	SimulationSetting ssetting;
	//ssetting.boundaryBox = Box( Vector3d( -1.0, -1.0, -1.0), Vector3d( 1.0, 1.0, 1.0 ) );
	//ssetting.particleDiameter = 0.1;
	//ssetting.
	factory.createPhysicsObject( condition, ssetting);
	
	visualParticles.resize( points.size() );

	renderer.init();
}