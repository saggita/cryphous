#ifndef __PARTICLE_FACTORY_H__
#define __PARTICLE_FACTORY_H__

#include <vector>
#include "Uncopyable.h"

#include "Particle.h"
#include "ParticleConditions.h"
#include "../CryphousGeometry/Vector3d.h"


namespace Cryphous{
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
		for( Particle* particle: particles ) { delete particle; }
		delete virtualParticle;
	}

	ParticleVector createParticles(const std::vector<Geometry::Vector3d>& points, const ParticleConditions& conditions)
	{
		for( const Geometry::Vector3d& point: points ) { particles.push_back( new Particle( nextID++, point, conditions ) ); }
		virtualParticle = new Particle( -1, Geometry::Vector3d(), conditions );
		return particles;
	}

	ParticleVector addParticles(const std::vector<Geometry::Vector3d>& points, const std::vector<Geometry::Vector3d>& velocities)
	{
		assert( virtualParticle );
		const ParticleConditions& condition = virtualParticle->condition;
		for( size_t i = 0; i < points.size(); ++i ) {
			particles.push_back( new Particle( nextID++, points[i], condition) );
			particles.back()->velocity = velocities[i];
		}
		return particles;
	}

	ParticleVector getParticles() const { return particles; }

	Particle* getVirtualParticle() { return virtualParticle; }

private:
	int nextID;
	ParticleVector particles;
	Particle* virtualParticle;
};

	}
}

#endif