#include "ParticleFactoryTest.h"

#include "../CrystalPhysics/ParticleFactory.h"
#include "../CrystalPhysics/ParticleConditions.h"

#include "../CrystalGeom/Vector3d.h"
#include "../CrystalGeom/Box.h"

#include <boost/test/unit_test.hpp>

using namespace Crystal::Geom;
using namespace Crystal::Physics;

ParticleFactoryTest::ParticleFactoryTest(void)
{
	std::vector<Vector3d> points;
	points.push_back( Vector3d(0.0, 0.0, 0.0 ) );
	points.push_back( Vector3d(1.0, 0.0, 0.0 ) );
	ParticleConditions conditions( points, 1.0, 1000.0); 
	ParticleFactory factory;
	const ParticleVector& particles = factory.createParticles( conditions );
	BOOST_CHECK( particles.size() == 2 );

	Particle* virtualParticle = factory.getVirtualParticle();
	BOOST_CHECK( virtualParticle != 0 );
}
