#ifndef __PARTICLE_FACTORY_H__
#define __PARTICLE_FACTORY_H__

#include <vector>
#include <boost/noncopyable.hpp>
#include <boost/foreach.hpp>

#include "Particle.h"
#include "ParticleConditions.h"
#include "../CrystalGeom/Vector3d.h"


namespace Crystal{
	namespace Physics{
		
class ParticleFactory : private boost::noncopyable
{
public:
	ParticleFactory(void):
	nextID(0),
		virtualParticle(0)
	{}

	~ParticleFactory(void)
	{
		BOOST_FOREACH( Particle* particle, particles ) {
			delete particle;
		}
		if( virtualParticle != 0 ) {
			delete virtualParticle;
		}
	}

	ParticleVector createParticles(const ParticleConditions& conditions)
	{
		std::vector<Geom::Vector3d>& innerPoints = conditions.getInnerPoints();
		BOOST_FOREACH( Geom::Vector3d& innerPoint, innerPoints ) {
			particles.push_back(
				new Particle( nextID++, innerPoint, conditions.getParticleMass(), conditions.getParticleLength() * 0.5f, this ) 
				);
			particles.back()->density = conditions.getDensity();
		}
		virtualParticle = new Particle( -1, Geom::Vector3d(), conditions.getParticleMass(), conditions.getParticleLength() * 0.5f, this );
		return particles;
	}

	ParticleVector getParticles() const { return particles; }

	Particle* getVirtualParticle() { return virtualParticle; }

private:
	void destroyVirtualParticle()
	{
		assert( virtualParticle != 0 );
		delete virtualParticle;
		virtualParticle = 0;
	}

private:
	int nextID;
	ParticleVector particles;
	Particle* virtualParticle;
};

	}
}

#endif