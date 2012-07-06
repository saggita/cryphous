#include "SearchParticleFactory.h"

#include "Particle.h"

#include "SearchParticle.h"

#include <algorithm>

#ifdef _OPENMP
#include <omp.h>
#endif

using namespace Crystal::Physics;

SearchParticleFactory::SearchParticleFactory(const ParticleVector& particles, const double effectLength)
{
	addParticles( particles, effectLength );
}

void SearchParticleFactory::addParticles(const ParticleVector& particles, const double effectLength)
{
	for( size_t i = 0; i < particles.size(); ++i ) {
		searchParticles.push_back( SearchParticle( particles[i], effectLength) );
	}

	std::sort( searchParticles.begin(), searchParticles.end() );
	return;
}

void SearchParticleFactory::init()
{
	searchParticles.clear();
}

ParticleVector SearchParticleFactory::getParticles() const
{
	ParticleVector particles;
	for( size_t i = 0; i < searchParticles.size(); ++i ) {
		particles.push_back( searchParticles[i].getParticle() );
	}
	return particles;
}

SearchParticleFactory::~SearchParticleFactory(void)
{
}