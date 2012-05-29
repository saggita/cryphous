#pragma once

#include "ParticlePair.h"
//#include "SearchParticle.h"

#include <set>
#include <vector>

namespace Crystal{
	namespace Physics{
		class SearchParticle;
		typedef std::vector<SearchParticle> SearchParticleVector;

class NeighborSearcher
{
public:
	NeighborSearcher(const SearchParticleVector& searchParticles,
		const double effectLength):
		searchParticles( searchParticles),
		effectLengthSquared( effectLength * effectLength)
	{};

	~NeighborSearcher(void);

	void search();

	ParticlePairVector getPairs() const { return pairs; }


private:

	void searchX();

	void searchNeighbors();

private:
	const SearchParticleVector& searchParticles;
	const double effectLengthSquared;
	ParticlePairVector pairs;
};

	}
}