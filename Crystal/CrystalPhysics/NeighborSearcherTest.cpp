#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include "../CrystalPhysics/NeighborSearcher.h"

#include "../CrystalPhysics/SearchParticleFactory.h"
#include "../CrystalPhysics/SearchParticle.h"

#include "../CrystalPhysics/Particle.h"
#include "../CrystalPhysics/ParticleFactory.h"
#include "../CrystalPhysics/ParticleConditions.h"
#include "../CrystalPhysics/SimulationSetting.h"

#include "../CrystalGeom/Box.h"

using namespace Crystal::Geom;
using namespace Crystal::Physics;


BOOST_AUTO_TEST_CASE(NEIGHBOR_SEARCHER_TEST)
{
	SimulationSetting setting;
	setting.particleDiameter = 1.0;
	std::vector<Vector3d> points;
	points.push_back( Vector3d( 0.0, 0.0, 0.0 ));
	points.push_back( Vector3d( 1.0, 0.0, 0.0 ));
	ParticleConditions conditions( 1.0, 1000.0, 1.0, 1.0); 
	ParticleFactory factory;
	const ParticleVector& particles = factory.createParticles( points, conditions );
	
	BOOST_CHECK_EQUAL( particles.size() , 2 );
	SearchParticleFactory searchFactory( particles, setting.getEffectLength() );
	SearchParticleVector& sorted = searchFactory.getSearchParticles();
	BOOST_CHECK_EQUAL( sorted.size(), 2 );

	NeighborSearcher searcher( sorted, setting.getEffectLength() );
	searcher.search();
	BOOST_CHECK( !searcher.getPairs().empty() );
}