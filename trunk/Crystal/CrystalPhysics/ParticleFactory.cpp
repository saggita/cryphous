#include "ParticleFactory.h"

#include "Particle.h"
#include "ParticleConditions.h"

#include "../CrystalGeom/Point3d.h"
#include "../CrystalGeom/Vector3d.h"

#include <boost/foreach.hpp>
#include <cstdlib>
#include <cassert>

using namespace Crystal::Physics;
using namespace Crystal::Geom;

ParticleFactory::ParticleFactory(void) :
nextID(0),
virtualParticle(0)
{
}

ParticleVector ParticleFactory::createParticles(const ParticleConditions& conditions)
{
	std::vector<Point3d>& innerPoints = conditions.getInnerPoints();
	BOOST_FOREACH( Point3d& innerPoint, innerPoints ) {
		particles.push_back(
			new Particle( nextID++, innerPoint, conditions.getParticleMass(), conditions.getParticleLength() * 0.5, this ) 
			);
		particles.back()->density = conditions.getDensity();
	}
	virtualParticle = new Particle( -1, Point3d(), conditions.getParticleMass(), conditions.getParticleLength() * 0.5, this );
	return particles;
}

void ParticleFactory::destroyVirtualParticle()
{
	assert( virtualParticle != 0 );
	delete virtualParticle;
	virtualParticle = 0;
}

ParticleFactory::~ParticleFactory(void)
{
	BOOST_FOREACH( Particle* particle, particles ) {
		delete particle;
	}
	if( virtualParticle != 0 ) {
		delete virtualParticle;
	}
}