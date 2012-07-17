#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include "../CrystalPhysics/SearchParticleFactory.h"
#include "../CrystalPhysics/SearchParticle.h"

#include "../CrystalPhysics/Particle.h"
#include "../CrystalPhysics/ParticleFactory.h"
#include "../CrystalPhysics/ParticleConditions.h"

#include "../CrystalGeom/Box.h"

using namespace Crystal::Geom;
using namespace Crystal::Physics;

BOOST_AUTO_TEST_CASE( SEARCH_PARTICLE_FACTORY_TEST )
{
	{
		std::vector<Vector3d> points;
		points.push_back( Vector3d(0.0, 0.0, 0.0 ) );
		ParticleConditions conditions( points, 1.0, 1000.0); 
		ParticleFactory factory;
		const ParticleVector& particles = factory.createParticles( conditions );
		BOOST_CHECK_EQUAL( particles.size() , 1 );
		SearchParticleFactory searchFactory( particles, 1.0 );
		SearchParticleVector& sorted = searchFactory.getSearchParticles();
		BOOST_CHECK_EQUAL( sorted.size(), 1 );
	}

	{
		std::vector<Vector3d> points;
		points.push_back( Vector3d(0.0, 0.0, 0.0 ) );
		ParticleConditions conditions( points, 1.0, 1000.0); 
		ParticleFactory factory;
		const ParticleVector& particles = factory.createParticles( conditions );
		SearchParticleFactory searchFactory;
		searchFactory.addParticles( particles, 1.0f );
		BOOST_CHECK_EQUAL( searchFactory.getSearchParticles().size(), 1 ); 
	}

	{
		std::vector<Vector3d> points;
		points.push_back( Vector3d(0.0, 0.0, 0.0 ) );
		ParticleConditions conditions( points, 1.0, 1000.0); 
		ParticleFactory factory;
		const ParticleVector& particles = factory.createParticles( conditions );
		BOOST_CHECK_EQUAL( particles.size() , 1 );
		SearchParticleFactory searchFactory( particles, 1.0 );
		BOOST_CHECK_EQUAL( searchFactory.getSearchParticles().size(), 1 );
	}

	{
		std::vector<Vector3d> points;
		points.push_back( Vector3d(0.0, 0.0, 0.0 ) );
		ParticleConditions conditions( points, 1.0, 1000.0); 
		ParticleFactory factory;
		const ParticleVector& particles = factory.createParticles( conditions );
		BOOST_CHECK_EQUAL( particles.size() , 1 );
		SearchParticleFactory searchFactory( particles, 1.0 );
		SearchParticleVector& sorted = searchFactory.getSearchParticles();
		BOOST_CHECK_EQUAL( sorted.size(), 1 );
		searchFactory.init();
		BOOST_CHECK( searchFactory.getSearchParticles().empty() );
	}
}