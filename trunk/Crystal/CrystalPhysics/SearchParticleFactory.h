#pragma once

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

	SearchParticleFactory(const ParticleVector& particles, const double effectLength);

	~SearchParticleFactory(void);

	void init();

	void addParticles(const ParticleVector& particles, const double effectLength);

	SearchParticleVector getSearchParticles() const { return searchParticles; }

	ParticleVector getParticles() const;

private:
	SearchParticleVector searchParticles;
};

	}
}