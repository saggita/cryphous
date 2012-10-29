#include "PhotonSolver.h"

#include "LightSourceFactory.h"
#include "SearchPhotonFactory.h"
#include "BoundaryPhotonSolver.h"
#include "SearchParticleFactory.h"
#include "NeighborPhotonSearcher.h"
#include "Profiler.h"

#include <random>

using namespace Crystal::Geom;
using namespace Crystal::Physics;

#ifdef _OPENMP
#include <omp.h>
#endif

PhotonSolver::~PhotonSolver(void)
{
	delete neighborSearcher;
}


void PhotonSolver::calculateInteraction(const SearchParticleVector& sortedParticles, const SearchPhotonVector& sortedPhotons)
{
	const LightSourceVector& lightSources = factory->getLightSources();
	
	for( LightSource* lightSource: lightSources ) {
		lightSource->initAbsorbedPhotons();
	}
	createPairs(sortedParticles, sortedPhotons);
	calculateBoundaryIntersection();
	
}

void PhotonSolver::createPairs(const SearchParticleVector& sortedParticles, const SearchPhotonVector& sortedPhotons)
{
	assert( neighborSearcher == 0 );
	
	Profiler::get()->start(" Sim->searchPhoton");
	neighborSearcher = new NeighborPhotonSearcher( sortedPhotons, setting.getEffectLength() );
	neighborSearcher->search( sortedParticles);
	Profiler::get()->end(" Sim->searchPhoton");
}

/*void PhotonSolver::calculateParticlePhotonIntersection()
{
	Profiler::get()->start(" Sim->photonIntersection");
	Profiler::get()->end(" Sim ->photonIntersection");
}*/

void PhotonSolver::calculateBoundaryIntersection()
{
	Profiler::get()->start(" Sim->boundaryPhoton");
	const LightSourceVector& lightSources = factory->getLightSources();	
	for( LightSource* lightSource : lightSources ) {
		BoundaryPhotonSolver solver( lightSource );
		solver.reflectPhoton( setting.boundaryBox );
	}
	Profiler::get()->end(" Sim->boundaryPhoton");
}