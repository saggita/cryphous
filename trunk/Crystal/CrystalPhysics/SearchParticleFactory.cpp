#include "SearchParticleFactory.h"

#include "Particle.h"

#include "SearchParticle.h"

#include <algorithm>

using namespace Crystal::Physics;

SearchParticleFactory::SearchParticleFactory(const ParticleVector& particles, const double effectLength)
{
	for( size_t i = 0; i < particles.size(); ++i ) {
		SearchParticle sParticle( particles[i], effectLength );
		searchParticles.push_back( sParticle );
	}
	std::sort( searchParticles.begin(), searchParticles.end() );
}

void SearchParticleFactory::addParticles(const ParticleVector& particles, const double effectLength)
{
	for( size_t i = 0; i < particles.size(); ++i ) {
		SearchParticle sParticle( particles[i], effectLength );
		searchParticles.push_back( sParticle );
	}
	std::sort( searchParticles.begin(), searchParticles.end() );
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