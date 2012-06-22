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

	#pragma omp parallel
	#pragma omp sections
	{
		#pragma omp section 
		{
			searchX(0, divides[0], divides[1] );
			searchNeighbors(0, divides[0], divides[1]);
		}

		#pragma omp section 
		{
			searchX(1, divides[1], divides[2] );
			searchNeighbors(1, divides[1], divides[2]);
		}

		#pragma omp section 
		{
			searchX(2, divides[2], divides[3] );
			searchNeighbors(2, divides[2], divides[3]);
		}

		#pragma omp section 
		{
			searchX(3, divides[3], divides[4] );
			searchNeighbors(3, divides[3], divides[4]);
		}

		#pragma omp section 
		{
			searchX(4, divides[4], divides[5] );
			searchNeighbors(4, divides[4], divides[5]);
		}

		#pragma omp section 
		{
			searchX(5, divides[5], divides[6] );
			searchNeighbors(5, divides[5], divides[6]);
		}

		#pragma omp section 
		{
			searchX(6, divides[6], divides[7] );
			searchNeighbors(6, divides[6], divides[7]);
		}

		#pragma omp section 
		{
			searchX(7, divides[7], searchParticles.size() );
			searchNeighbors(7, divides[7], searchParticles.size());
		}
	}

	for( size_t i = 0; i < eachPairs.size(); ++i ) {
		pairs.insert( pairs.end(), eachPairs[i].begin(), eachPairs[i].end() );
	}
}

void NeighborSearcher::searchNeighbors(int number, int startIndex, int endIndex)
{
	int yIndex[4];// = startIndex;
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
			// std::vector<SearchParticle>::const_iterator yIter = std::lower_bound(searchParticles.begin(), searchParticles.end(), baseID);

			int zIndex = yIndex[i];
			//std::vector<SearchParticle>::const_iterator zIter = yIter; 
			const Point3d& centerX = searchParticles[index].getCenter();
			while( zIndex < searchParticles.size() && searchParticles[zIndex].getGridID() <= baseID+2 ) {
			//while( zIter != searchParticles.end() && zIter->getGridID() <= baseID+2 ) {
				const Point3d& centerZ = searchParticles[zIndex].getCenter();
				//const Point3d& centerZ = zIter->getCenter();
				if( centerX.getDistanceSquared( centerZ ) < effectLengthSquared ) {
					//eachPairs[number].push_back( new ParticlePair( searchParticles[index].getParticle(), zIter->getParticle() ) );
					eachPairs[number].push_back( new ParticlePair( searchParticles[index].getParticle(),searchParticles[zIndex].getParticle() ) );
				}
				++zIndex;
				//++zIter;
			}
		}
	}
}

void NeighborSearcher::searchX(int number, int startIndex, int endIndex)
{
	for( int index = startIndex; index < endIndex; ++index ) {
		const int gridID = searchParticles[index].getGridID();
		const Point3d& centerX = searchParticles[index].getCenter();
		int xIndex = index;
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