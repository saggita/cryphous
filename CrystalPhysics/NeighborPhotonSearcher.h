#ifndef __NEIGHBOR_PHOTON_SEARCHER_H__
#define __NEIGHBOR_PHOTON_SEARCHER_H__

#include "SearchPhoton.h"

#include <vector>

namespace Crystal{
	namespace Physics{
		class SearchParticle;
		typedef std::vector<SearchParticle> SearchParticleVector;

class NeighborPhotonSearcher
{
public:
	NeighborPhotonSearcher(const SearchPhotonVector& photons,
		const float effectLength):
		photons( photons),
		effectLengthSquared( effectLength * effectLength)
	{};

	~NeighborPhotonSearcher(void){};

	void search(const SearchParticleVector& particles);

private:

	void search(SearchPhotonVector::const_iterator startIter, SearchPhotonVector::const_iterator endIter, const SearchParticleVector& particles);

	const SearchPhotonVector& photons;
	const float effectLengthSquared;
};

	}
}

#endif