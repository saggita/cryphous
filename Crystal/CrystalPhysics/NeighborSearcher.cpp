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
	std::vector<ParticlePairVector> eachPairs(5);
	#pragma omp parallel
	#pragma omp sections
	{
		#pragma omp section 
		{
			eachPairs[0] = searchNeighbors(0);
		}

		#pragma omp section 
		{
			eachPairs[1] = searchNeighbors(1);
		}

		#pragma omp section 
		{
			eachPairs[2] = searchNeighbors(2);
		}

		#pragma omp section 
		{
			eachPairs[3] = searchNeighbors(3);
		}

		#pragma omp section 
		{
			eachPairs[4] = searchX();
		}
	}

	for( size_t i = 0; i < eachPairs.size(); ++i ) {
		pairs.insert( pairs.end(), eachPairs[i].begin(), eachPairs[i].end() );
	}
}

ParticlePairVector NeighborSearcher::searchNeighbors(const int number)
{
	ParticlePairVector eachPairs;
	SearchParticleVector::const_iterator baseIter = searchParticles.begin();
	
	for( SearchParticleVector::const_iterator iter = searchParticles.begin(); iter != searchParticles.end(); ++iter ) {
		const int baseID = iter->getForwardIDs()[number];
		while( baseIter != searchParticles.end() && baseIter->getGridID() < baseID ) {
			++baseIter;
		}
		SearchParticleVector::const_iterator yIter = baseIter;
			
		const Point3d& centerX = iter->getCenter();
		while( yIter != searchParticles.end() && yIter->getGridID() <= baseID+2 ) {
			const Point3d& centerY = yIter->getCenter();
			if( centerX.getDistanceSquared( centerY ) < effectLengthSquared ) {
				eachPairs.push_back( new ParticlePair( iter->getParticle(), yIter->getParticle() ) );
			}
			++yIter;
		}
	}
	return eachPairs;
}

ParticlePairVector NeighborSearcher::searchX()
{
	ParticlePairVector eachPairs;
	for( SearchParticleVector::const_iterator iter = searchParticles.begin(); iter != searchParticles.end(); ++iter ) {
		const int gridID = iter->getGridID();
		const Point3d& centerX = iter->getCenter();
		SearchParticleVector::const_iterator xIter = iter;
		++xIter;
		while( xIter != searchParticles.end() && xIter->getGridID() <= gridID+1 ) {
			const Point3d& centerY = xIter->getCenter();
			if( centerX.getDistanceSquared( centerY ) < effectLengthSquared ) {
				eachPairs.push_back( new ParticlePair( iter->getParticle(), xIter->getParticle() ) );
			}
			++xIter;
		}
	}
	return eachPairs;
}

NeighborSearcher::~NeighborSearcher()
{
	for( size_t i = 0; i < pairs.size(); ++i ) {
		delete pairs[i];
	}
}