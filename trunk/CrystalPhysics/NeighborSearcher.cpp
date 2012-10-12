#include "NeighborSearcher.h"

#ifdef _OPENMP
#include <omp.h>
#endif

using namespace Crystal::Geom;
using namespace Crystal::Physics;

void NeighborSearcher::search()
{
		const int threads = 8; 
		eachPairs.resize(threads);

		std::vector<SearchParticleVector::const_iterator> iters;
		for( int i = 0; i < threads; ++i ) {
			iters.push_back( searchParticles.begin() + i * searchParticles.size() / threads );
		}
		iters.push_back( searchParticles.end() );

		#pragma omp parallel for
		for( int i = 0; i < threads; ++i ) {
			searchX(i, iters[i], iters[i+1] );
			searchNeighbors(i, iters[i], iters[i+1] );
		}

		for( size_t i = 0; i < eachPairs.size(); ++i ) {
			pairs.insert( pairs.end(), eachPairs[i].begin(), eachPairs[i].end() );
		}
}

void NeighborSearcher::searchX(int number, SearchParticleVector::const_iterator startIter, SearchParticleVector::const_iterator endIter){
		for( SearchParticleVector::const_iterator xIter = startIter; xIter != endIter; ++xIter ) {
			const int gridID = xIter->getGridID();
			const Geom::Vector3d& centerX = xIter->getCenter();
			SearchParticleVector::const_iterator yIter = xIter;
			++yIter;// ignore itself.
			while( yIter != searchParticles.end() && (yIter->getGridID() <= gridID + 1) ) {
				const Geom::Vector3d& centerY = yIter->getCenter();
				if( centerX.getDistanceSquared( centerY ) < effectLengthSquared ) {
					eachPairs[number].push_back( ParticlePair( xIter->getParticle(), yIter->getParticle() ) );
				}
				++yIter;
			}
		}
}

void NeighborSearcher::searchNeighbors(int number, SearchParticleVector::const_iterator startIter, SearchParticleVector::const_iterator endIter)
{
		std::vector<SearchParticleVector::const_iterator> yIter(4, startIter);
		std::vector<int> offsetIds;
		offsetIds.push_back(1023);
		offsetIds.push_back(1047551);
		offsetIds.push_back(1048575);
		offsetIds.push_back(1049599);

		for( SearchParticleVector::const_iterator xIter = startIter; xIter != endIter; ++xIter ) {
			for( size_t i = 0; i < offsetIds.size(); ++i ) {
				const int baseID = xIter->getGridID() + offsetIds[i];
				while( yIter[i] != searchParticles.end() && ( yIter[i]->getGridID() < baseID ) ) {
					++yIter[i];
				}
			
				const Geom::Vector3d& centerX = xIter->getCenter();
				SearchParticleVector::const_iterator zIter = yIter[i];
				while( zIter != searchParticles.end() && (zIter->getGridID() <= baseID + 2) ) {
					const Geom::Vector3d& centerZ = zIter->getCenter();
					if( centerX.getDistanceSquared( centerZ ) < effectLengthSquared ) {
						eachPairs[number].push_back( ParticlePair( xIter->getParticle(), zIter->getParticle() ) );
					}
					++zIter;
				}
			}
		}
}