#ifndef __PARTICLE_FACTORY_H__
#define __PARTICLE_FACTORY_H__

#include <vector>
#include <boost/noncopyable.hpp>

namespace Crystal{
	namespace Geom {
		class Vector3d;
	}
	namespace Physics{
		class ParticleConditions;
		class Particle;
		typedef std::vector<Particle*> ParticleVector;

class ParticleFactory : private boost::noncopyable
{
public:
	ParticleFactory(void):
	nextID(0),
		virtualParticle(0)
	{}

	~ParticleFactory(void);

	ParticleVector createParticles(const ParticleConditions& conditions);

	ParticleVector getParticles() const { return particles; }

	Particle* getVirtualParticle() { return virtualParticle; }

private:
	void destroyVirtualParticle();

private:
	int nextID;
	ParticleVector particles;
	Particle* virtualParticle;
};

	}
}

#endif