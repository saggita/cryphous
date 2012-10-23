#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include "../CrystalPhysics/NeighborPhotonSearcher.h"

#include "../CrystalPhysics/SearchPhotonFactory.h"
#include "../CrystalPhysics/SearchPhoton.h"

#include "../CrystalPhysics/Photon.h"
#include "../CrystalPhysics/PhotonFactory.h"
#include "../CrystalPhysics/SimulationSetting.h"

#include "../CrystalPhysics/ParticleFactory.h"
#include "../CrystalPhysics/Particle.h"
#include "../CrystalPhysics/ParticleConditions.h"
#include "../CrystalPhysics/SearchParticle.h"
#include "../CrystalPhysics/SearchParticleFactory.h"

using namespace Crystal::Geom;
using namespace Crystal::Physics;


BOOST_AUTO_TEST_CASE(NEIGHBOR_PHOTON_SEARCHER_TEST)
{
	SimulationSetting setting;
	setting.particleDiameter = 1.0;
	std::vector<Vector3d> points;
	points.push_back( Vector3d( 0.0, 0.0, 0.0 ));
	ParticleConditions conditions( 1.0, 1000.0, 1.0, 1.0); 
	ParticleFactory factory;
	const ParticleVector& particles = factory.createParticles( points, conditions );
	
	BOOST_CHECK_EQUAL( particles.size() , 1 );

	SearchParticleFactory searchFactory( particles, setting.getEffectLength() );

	SearchParticleVector& sortedParticles = searchFactory.getSearchParticles();
	BOOST_CHECK_EQUAL( sortedParticles.size(), 1 );

	std::vector<Vector3d> velocities;
	velocities.push_back( Vector3d( 1.0, 0.0, 0.0));
	PhotonFactory pFactory;
	const PhotonVector& photons = pFactory.addPhotons( points, velocities );
	SearchPhotonFactory spFactory( photons, setting.getEffectLength() );
	SearchPhotonVector& sortedPhotons = spFactory.getSearchPhotons();

	NeighborPhotonSearcher pSearcher( sortedPhotons, setting.getEffectLength() );
	pSearcher.search( sortedParticles);
}