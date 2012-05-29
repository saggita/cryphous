#include "SpringTest.h"

#include "../CrystalPhysics/Spring.h"

#include "../CrystalPhysics/Particle.h"
#include "../CrystalPhysics/ParticleDerive.h"
#include "../CrystalPhysics/ParticleFactory.h"
#include "../CrystalPhysics/ParticleConditions.h"

#include "../CrystalGeom/Box.h"
#include "../CrystalGeom/Point3d.h"
#include "../CrystalGeom/Vector3d.h"
#include "../CrystalGeom/Line.h"

#include <boost/test/unit_test.hpp>

using namespace Crystal::Geom;
using namespace Crystal::Physics;

SpringTest::SpringTest(void)
{
	getLineTest();
	enforceTest();
}

void SpringTest::getLineTest()
{
	ParticleConditions conditions( Box( Point3d( 0.0, 0.0, 0.0), Point3d( 5.0, 5.0, 5.0)), 1.0, 1000.0 );
	ParticleFactory factory;
	const ParticleVector& particles = factory.createParticles( conditions );
	Spring spring( particles.front(), particles.back() );
	const Line& line = spring.getLine();
	BOOST_CHECK( line == Line( Point3d( 0.5, 0.5, 0.5), Point3d( 4.5, 4.5, 4.5 ) ) );
}

void SpringTest::enforceTest()
{
	ParticleConditions conditions( Box( Point3d( 0.0, 0.0, 0.0), Point3d( 5.0, 5.0, 5.0)), 1.0, 1000.0 );
	ParticleFactory factory;
	const ParticleVector& particles = factory.createParticles( conditions );
	Spring springX( particles.front(), particles.back() );
	springX.enforce( 1.0, 0.1);
	Spring springY( particles.back(), particles.front() );
	springY.enforce( 1.0, 0.1);
	BOOST_CHECK( particles.front()->getDerive()->force == -1.0 * particles.back()->getDerive()->force );
}