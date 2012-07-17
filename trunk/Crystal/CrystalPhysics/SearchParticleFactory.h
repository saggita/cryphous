#ifndef __SEARCH_PARTICLE_FACTORY_H__
#define __SEARCH_PARTICLE_FACTORY_H__

#include <vector>
#include "SearchParticle.h"

namespace Crystal{
	namespace Physics{
		class Particle;
		typedef std::vector<Particle*> ParticleVector;

class SearchParticleFactory
{
public:

	SearchParticleFactory(){};

	SearchParticleFactory(const ParticleVector& particles, const float effectLength);

	~SearchParticleFactory(void);

	void init();

	void addParticles(const ParticleVector& particles, const float effectLength);

	SearchParticleVector getSearchParticles() const { return searchParticles; }

	ParticleVector getParticles() const;

private:
	SearchParticleVector searchParticles;
};

	}
}

#endif