#ifndef __SEARCH_PARTICLE_FACTORY_H__
#define __SEARCH_PARTICLE_FACTORY_H__

#include <vector>
#include <algorithm>
#include "SearchParticle.h"
#include "Particle.h"

namespace Cryphous{
	namespace Physics{
		
class SearchParticleFactory
{
public:

	SearchParticleFactory(){};

	SearchParticleFactory(const ParticleVector& particles, const float effectLength) { addParticles( particles, effectLength ); }

	~SearchParticleFactory(void){};

	void init() { searchParticles.clear(); }

	void addParticles(const ParticleVector& particles, const float effectLength)
	{
		for( size_t i = 0; i < particles.size(); ++i ) {
			searchParticles.push_back( SearchParticle( particles[i], effectLength) );
		}
		std::sort( searchParticles.begin(), searchParticles.end() );
		return;
	}

	SearchParticleVector getSearchParticles() const { return searchParticles; }

	ParticleVector getParticles() const
	{
		ParticleVector particles;
		for( size_t i = 0; i < searchParticles.size(); ++i ) {
			particles.push_back( searchParticles[i].getParticle() );
		}
		return particles;
	}

private:
	SearchParticleVector searchParticles;
};

	}
}

#endif