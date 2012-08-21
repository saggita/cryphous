#include "StdAfx.h"
#include "VisualParticleTest.h"

using namespace Amorphous::Geom;
using namespace Amorphous::Color;

VisualParticleTest::VisualParticleTest(void)
{
	createVisualParticlesTest();
}

void VisualParticleTest::createVisualParticlesTest()
{
	VisualParticleList vParticles;
	vParticles.push_back( VisualParticle( Vector3d<>( 0.0, 0.0, 0.0), 2500.0, 1.0, Vector3d<>( 0.0, 1.0, 0.0) ) );
	BOOST_CHECK( vParticles.size() == 1 );
	BOOST_CHECK( vParticles.front().center == Vector3d<>( 0.0, 0.0, 0.0 ) );
}