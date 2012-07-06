#include "NeighborSearcher.h"

#include "SearchParticleFactory.h"
#include "SearchParticle.h"
#include "Particle.h"
#include "SimulationSetting.h"
#include "ParticlePair.h"
#include "../CrystalGeom/Vector3d.h"

#include "ParticleFactory.h"
#include "PhysicsObject.h"
#include "PhysicsObjectFactory.h"

#include <algorithm>

#include "Profiler.h"

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

void NeighborSearcher::searchNeighbors(int number, SearchParticleVector::const_iterator startIter, SearchParticleVector::const_iterator endIter)
{
	std::vector<SearchParticleVector::const_iterator> yIter(4, startIter);

	for( SearchParticleVector::const_iterator xIter = startIter; xIter != endIter; ++xIter ) {
		const std::vector<int>& ids = xIter->getForwardIDs();
		for( size_t i = 0; i < ids.size(); ++i ) {
			const int baseID = ids[i];
			yIter[i] = std::lower_bound( yIter[i], searchParticles.end(), baseID );
			SearchParticleVector::const_iterator secondIter = std::upper_bound( yIter[i], searchParticles.end(), baseID+2 );

			const Vector3d& centerX = xIter->getCenter();
			for( SearchParticleVector::const_iterator zIter = yIter[i]; zIter != secondIter; ++zIter ) {
				const Vector3d& centerZ = zIter->getCenter();
				if( centerX.getDistanceSquared( centerZ ) < effectLengthSquared ) {
					eachPairs[number].push_back( ParticlePair( xIter->getParticle(), zIter->getParticle() ) );
				}
			}
		}
	}
}

void NeighborSearcher::searchX(int number, SearchParticleVector::const_iterator startIter, SearchParticleVector::const_iterator endIter)
{
	for( SearchParticleVector::const_iterator xIter = startIter; xIter != endIter; ++xIter ) {
		const int gridID = xIter->getGridID();
		const Vector3d& centerX = xIter->getCenter();
		SearchParticleVector::const_iterator yIter = xIter;
		++yIter;// ignore itself.
		SearchParticleVector::const_iterator endIter = std::upper_bound( yIter, searchParticles.end(), gridID+1 );
		while( yIter != endIter ) {
			const Vector3d& centerY = yIter->getCenter();
			if( centerX.getDistanceSquared( centerY ) < effectLengthSquared ) {
				eachPairs[number].push_back( ParticlePair( xIter->getParticle(), yIter->getParticle() ) );
			}
			++yIter;
		}
	}
}