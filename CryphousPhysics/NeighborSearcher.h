#ifndef __NEIGHBOR_SEARCHER_H__
#define __NEIGHBOR_SEARCHER_H__

#include "ParticlePair.h"
#include "SearchParticle.h"
#include "Profiler.h"

#include <vector>

namespace Cryphous{
	namespace Physics{

class NeighborSearcher
{
public:
	NeighborSearcher(const SearchParticleVector& searchParticles,
		const float effectLength):
		searchParticles( searchParticles),
		effectLengthSquared( effectLength * effectLength)
	{};

	~NeighborSearcher(void){};

	void search();

	ParticlePairVector getPairs() const { return pairs; }


private:

	void searchX(int number, SearchParticleVector::const_iterator startIter, SearchParticleVector::const_iterator endIter);

	void searchNeighbors(int number, SearchParticleVector::const_iterator startIter, SearchParticleVector::const_iterator endIter);


private:
	const SearchParticleVector& searchParticles;
	const float effectLengthSquared;
	ParticlePairVector pairs;
	std::vector<ParticlePairVector> eachPairs;

};

	}
}

#endif