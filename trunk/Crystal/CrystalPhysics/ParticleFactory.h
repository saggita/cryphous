#ifndef __PARTICLE_FACTORY_H__
#define __PARTICLE_FACTORY_H__

#include <vector>
#include "../CrystalUtility/Uncopyable.h"

#include "Particle.h"
#include "ParticleConditions.h"
#include "../CrystalGeom/Vector3d.h"


namespace Crystal{
	namespace Physics{
		
class ParticleFactory : private Uncopyable
{
public:
	ParticleFactory(void):
	nextID(0),
		virtualParticle(0)
	{}

	~ParticleFactory(void)
	{
		for( ParticleVector::iterator iter = particles.begin(); iter != particles.end(); ++iter ) {
			delete (*iter);
		}
		if( virtualParticle != 0 ) {
			delete virtualParticle;
		}
	}

	ParticleVector createParticles(const std::vector<Geom::Vector3d>& points, const ParticleConditions& conditions)
	{
		for( std::vector<Geom::Vector3d>::const_iterator iter = points.begin(); iter != points.end(); ++ iter ) {
			particles.push_back( new Particle( nextID++, *(iter), conditions ) );
			particles.back()->density = conditions.getDensity();
		}
		virtualParticle = new Particle( -1, Geom::Vector3d(), conditions );
		return particles;
	}

	ParticleVector addParticles(const std::vector<Geom::Vector3d>& points, const std::vector<Geom::Vector3d>& velocities)
	{
		assert( virtualParticle );
		const ParticleConditions& condition = virtualParticle->condition;
		for( size_t i = 0; i < points.size(); ++i ) {
			particles.push_back( new Particle( nextID++, points[i], condition) );
			particles.back()->density = condition.getDensity();
			particles.back()->velocity = velocities[i];
		}
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