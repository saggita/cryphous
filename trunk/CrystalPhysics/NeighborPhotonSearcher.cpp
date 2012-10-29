#include "NeighborPhotonSearcher.h"

#include "SearchParticle.h"

#ifdef _OPENMP
#include <omp.h>
#endif

using namespace Crystal::Geom;
using namespace Crystal::Physics;

void NeighborPhotonSearcher::search(const SearchParticleVector& particles)
{
	const int threads = 8; 
		
	std::vector<SearchPhotonVector::const_iterator> iters;
	for( int i = 0; i < threads; ++i ) {
		iters.push_back( photons.begin() + i * photons.size() / threads );
	}
	iters.push_back( photons.end() );

	#pragma omp parallel for
	for( int i = 0; i < threads; ++i ) {
		search(iters[i], iters[i+1], particles );
	}
}

void NeighborPhotonSearcher::search(SearchPhotonVector::const_iterator startIter, SearchPhotonVector::const_iterator endIter, const SearchParticleVector& particles){
	SearchParticleVector::const_iterator yIter = particles.begin();
	for( SearchPhotonVector::const_iterator xIter = startIter; xIter != endIter; ++xIter ) {
		const int gridID = xIter->getGridID();
		const Geom::Vector3d& centerX = xIter->getCenter();
		while( yIter != particles.end() && (yIter->getGridID() <= gridID) ) {
			const Geom::Vector3d& centerY = yIter->getCenter();
			if( centerX.getDistanceSquared( centerY ) < effectLengthSquared ) {
				++(xIter->getPhoton()->absorbedTime);
			}
			++yIter;
		}
	}
}