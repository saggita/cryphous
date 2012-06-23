#include "NeighborSearcher.h"

#include "SearchParticleFactory.h"
#include "SearchParticle.h"
#include "Particle.h"
#include "SimulationSetting.h"
#include "ParticlePair.h"
#include "../CrystalGeom/Point3d.h"

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

	std::vector<int> divides(threads);
	for( int i = 0; i < threads; ++i ) {
		divides[i] = searchParticles.size() / threads * i;
	}
	divides.push_back( searchParticles.size() );

#pragma omp parallel for
	for( int i = 0; i < threads; ++i ) {
		searchX(i, divides[i], divides[i+1] );
		searchNeighbors(i, divides[i], divides[i+1] );
	}

	for( size_t i = 0; i < eachPairs.size(); ++i ) {
		pairs.insert( pairs.end(), eachPairs[i].begin(), eachPairs[i].end() );
	}
}

void NeighborSearcher::searchNeighbors(int number, int startIndex, int endIndex)
{
	size_t yIndex[4];
	for( int i = 0; i < 4; ++i ) {
		yIndex[i] = startIndex;
	}

	for( int index = startIndex; index < endIndex; ++index ) {
		const std::vector<int>& ids = searchParticles[index].getForwardIDs();
		for( size_t i = 0; i < ids.size(); ++i ) {
			const int baseID = ids[i];
			while( yIndex[i] < searchParticles.size() && searchParticles[yIndex[i]].getGridID() < baseID ) {
				++yIndex[i];
			}
			
			unsigned int zIndex = yIndex[i];
			const Point3d& centerX = searchParticles[index].getCenter();
			while( zIndex < searchParticles.size() && searchParticles[zIndex].getGridID() <= baseID+2 ) {
				const Point3d& centerZ = searchParticles[zIndex].getCenter();
				if( centerX.getDistanceSquared( centerZ ) < effectLengthSquared ) {
					eachPairs[number].push_back( new ParticlePair( searchParticles[index].getParticle(),searchParticles[zIndex].getParticle() ) );
				}
				++zIndex;
			}
		}
	}
}

void NeighborSearcher::searchX(int number, int startIndex, int endIndex)
{
	for( int index = startIndex; index < endIndex; ++index ) {
		const int gridID = searchParticles[index].getGridID();
		const Point3d& centerX = searchParticles[index].getCenter();
		unsigned int xIndex = index;
		++xIndex; // ignore itself.
		while( xIndex < searchParticles.size() && searchParticles[xIndex].getGridID() <= gridID+1 ) {
			const Point3d& centerY = searchParticles[xIndex].getCenter();
			if( centerX.getDistanceSquared( centerY ) < effectLengthSquared ) {
				eachPairs[number].push_back( new ParticlePair( searchParticles[index].getParticle(), searchParticles[xIndex].getParticle() ) );
			}
			++xIndex;
		}
	}
}

NeighborSearcher::~NeighborSearcher()
{
	for( size_t i = 0; i < pairs.size(); ++i ) {
		delete pairs[i];
	}
}