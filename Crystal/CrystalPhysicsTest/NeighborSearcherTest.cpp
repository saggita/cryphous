#include "NeighborSearcherTest.h"

#include "../CrystalPhysics/NeighborSearcher.h"

#include "../CrystalPhysics/SearchParticleFactory.h"
#include "../CrystalPhysics/SearchParticle.h"

#include "../CrystalPhysics/Particle.h"
#include "../CrystalPhysics/ParticleFactory.h"
#include "../CrystalPhysics/ParticleConditions.h"

#include "../CrystalGeom/Box.h"

#include "../CrystalPhysics/SimulationSetting.h"

#include <boost/test/unit_test.hpp>
#include <boost/timer.hpp>

#include <iostream>

using namespace Crystal::Geom;
using namespace Crystal::Physics;

NeighborSearcherTest::NeighborSearcherTest(void)
{
	searchTest();
}

NeighborSearcherTest::~NeighborSearcherTest(void)
{
}

void NeighborSearcherTest::searchTest()
{
	SimulationSetting setting;
	setting.particleDiameter = 1.0;
	ParticleConditions conditions( Box( Point3d( 0.0, 0.0, 0.0), Point3d( 10.0, 10.0, 10.0)), 1.0, 1000.0); 
	ParticleFactory factory;
	const ParticleVector& particles = factory.createParticles( conditions );
	
	BOOST_CHECK_EQUAL( particles.size() , 1000 );
	SearchParticleFactory searchFactory( particles, setting.getEffectLength() );
	SearchParticleVector& sorted = searchFactory.getSearchParticles();
	BOOST_CHECK_EQUAL( sorted.size(), 1000 );

	NeighborSearcher searcher( sorted, setting.getEffectLength() );
	searcher.search();
	BOOST_CHECK( !searcher.getPairs().empty() );
}