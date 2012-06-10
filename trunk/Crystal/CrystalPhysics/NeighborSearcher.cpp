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
#include "Profiler.h"

#include <algorithm>
#include <assert.h>

#include "Profiler.h"

#ifdef _OPENMP
#include <omp.h>
#endif

using namespace Crystal::Geom;
using namespace Crystal::Physics;

void NeighborSearcher::search()
{
	std::vector<ParticlePairVector> eachPairs(5);
	
	
	Profiler::get()->start("searchY");
	
	eachPairs[0] = searchNeighbors(0);
	eachPairs[1] = searchNeighbors(1);
	eachPairs[2] = searchNeighbors(2);
	eachPairs[3] = searchNeighbors(3);

	Profiler::get()->end("searchY");

	eachPairs[4] = searchX();


	for( size_t i = 0; i < eachPairs.size(); ++i ) {
		pairs.insert( pairs.end(), eachPairs[i].begin(), eachPairs[i].end() );
	}
}

ParticlePairVector NeighborSearcher::searchNeighbors(const int number)
{
	ParticlePairVector eachPair;
	std::vector<ParticlePairVector> eachPairs( searchParticles.size() );
	
	Profiler::get()->start("searchStart");
	std::vector<SearchParticleVector::const_iterator> startIters;
	SearchParticleVector::const_iterator startIter = searchParticles.begin();
	for( SearchParticleVector::const_iterator iter = searchParticles.begin(); iter != searchParticles.end(); ++iter) {
		const int startID = iter->getForwardIDs()[number];
		while( startIter != searchParticles.end() && startIter->getGridID() < startID ) {
			++startIter;
		}
		startIters.push_back( startIter );
	}
	assert( searchParticles.size() == startIters.size() );
	Profiler::get()->end("searchStart");

	#pragma omp parallel for
	for( int i = 0; i < (int)searchParticles.size(); ++i ) {
		SearchParticleVector::const_iterator startIter = startIters[i];
		if( startIter == searchParticles.end() ) {
			continue;
		}
		const int startID = startIter->getGridID();
		
		SearchParticleVector::const_iterator yIter = startIter;
			
		const Point3d& centerX = searchParticles[i].getCenter();
		Particle* particleX = searchParticles[i].getParticle();
		while( yIter != searchParticles.end() && yIter->getGridID() <= startID+2 ) {
			const Point3d& centerY = yIter->getCenter();
			if( centerX.getDistanceSquared( centerY ) < effectLengthSquared ) {
				eachPairs[i].push_back( new ParticlePair( particleX, yIter->getParticle() ) );
			}
			++yIter;
		}
	}
	
	for( size_t i = 0; i < eachPairs.size(); ++i ) {
		eachPair.insert( eachPair.end(), eachPairs[i].begin(), eachPairs[i].end() );
	}

	return eachPair;
}

ParticlePairVector NeighborSearcher::searchX()
{
	ParticlePairVector eachPair;
	std::vector<ParticlePairVector> eachPairs( searchParticles.size() );

	#pragma omp parallel for
	for( int i = 0; i < (int)searchParticles.size(); ++i ) {
		const int gridID = searchParticles[i].getGridID();
		const Point3d& centerX = searchParticles[i].getCenter();
		size_t searchIndex = i + 1;
		Particle* particle = searchParticles[i].getParticle();
		while( searchIndex < searchParticles.size() && searchParticles[searchIndex].getGridID() <= gridID + 1 ) {
			const Point3d& centerY = searchParticles[searchIndex].getCenter();
			if( centerX.getDistanceSquared( centerY ) < effectLengthSquared ) {
				eachPairs[i].push_back( new ParticlePair( particle, searchParticles[searchIndex].getParticle() ) );
			}
			++searchIndex;
		}
	}
	for( size_t i = 0; i < eachPairs.size(); ++i ) {
		eachPair.insert( eachPair.end(), eachPairs[i].begin(), eachPairs[i].end() );
	}
	return eachPair;
}

NeighborSearcher::~NeighborSearcher()
{
	for( size_t i = 0; i < pairs.size(); ++i ) {
		delete pairs[i];
	}
}