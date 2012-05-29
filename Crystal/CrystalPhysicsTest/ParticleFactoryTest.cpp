#include "ParticleFactoryTest.h"

#include "../CrystalPhysics/ParticleFactory.h"
#include "../CrystalPhysics/ParticleConditions.h"

#include "../CrystalGeom/Point3d.h"
#include "../CrystalGeom/Box.h"

#include <boost/test/unit_test.hpp>

using namespace Crystal::Geom;
using namespace Crystal::Physics;

ParticleFactoryTest::ParticleFactoryTest(void)
{
	ParticleConditions conditions( Box( Point3d( 0.0, 0.0, 0.0), Point3d( 10.0, 1.0, 1.0)), 1.0, 1000.0); 
	ParticleFactory factory;
	const ParticleVector& particles = factory.createParticles( conditions );
	BOOST_CHECK( particles.size() == 10 );

	Particle* virtualParticle = factory.getVirtualParticle();
	BOOST_CHECK( virtualParticle != 0 );
}
