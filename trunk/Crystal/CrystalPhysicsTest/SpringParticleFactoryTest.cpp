#include "SpringParticleFactoryTest.h"

#include "../CrystalPhysics/SpringParticleFactory.h"

#include "../CrystalPhysics/Particle.h"
#include "../CrystalPhysics/ParticleFactory.h"
#include "../CrystalPhysics/ParticleConditions.h"

#include "../CrystalGeom/Box.h"
#include "../CrystalGeom/Point3d.h"
#include "../CrystalGeom/Vector3d.h"
#include "../CrystalGeom/Line.h"

#include <boost/test/unit_test.hpp>

using namespace Crystal::Geom;
using namespace Crystal::Physics;

SpringParticleFactoryTest::SpringParticleFactoryTest(void)
{
	createSpringParticlesTest();
	getLinesTest();
}

void SpringParticleFactoryTest::createSpringParticlesTest()
{
	ParticleConditions conditions( Box( Point3d( 0.0, 0.0, 0.0), Point3d( 2.0, 2.0, 2.0)), 1.0, 1000.0 );
	ParticleFactory factory;
	const ParticleVector& particles = factory.createParticles( conditions );
	BOOST_CHECK( particles.size() == 8 );
	SpringParticleFactory gridFactory( particles, 2, 2, 2 );
	const size_t result = gridFactory.getSpringParticles().size();
	BOOST_CHECK_EQUAL( result, 8 );
}

void SpringParticleFactoryTest::getLinesTest()
{
	ParticleConditions conditions( Box( Point3d( 0.0, 0.0, 0.0), Point3d( 2.0, 2.0, 2.0)), 1.0, 1000.0 );
	ParticleFactory factory;
	const ParticleVector& particles = factory.createParticles( conditions );
	BOOST_CHECK( particles.size() == 8 );
	SpringParticleFactory gridFactory( particles, 2, 2, 2 );
	const LineList& lines = gridFactory.getLines();
	BOOST_CHECK( !lines.empty() );
}
