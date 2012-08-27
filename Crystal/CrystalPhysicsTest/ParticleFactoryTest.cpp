#define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include "../CrystalPhysics/ParticleFactory.h"
#include "../CrystalPhysics/ParticleConditions.h"

#include "../CrystalGeom/Vector3d.h"
#include "../CrystalGeom/Box.h"

using namespace Crystal::Geom;
using namespace Crystal::Physics;

BOOST_AUTO_TEST_CASE(PARTICLE_FACTORY_TEST)
{
	std::vector<Vector3d> points;
	points.push_back( Vector3d(0.0, 0.0, 0.0 ) );
	points.push_back( Vector3d(1.0, 0.0, 0.0 ) );
	ParticleConditions conditions( 1.0, 1000.0, 1.0, 1.0); 
	ParticleFactory factory;
	const ParticleVector& particles = factory.createParticles( points, conditions );
	BOOST_CHECK( particles.size() == 2 );

	Particle* virtualParticle = factory.getVirtualParticle();
	BOOST_CHECK( virtualParticle != 0 );
}
