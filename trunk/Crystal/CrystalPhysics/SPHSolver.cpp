#include "SPHSolver.h"

using namespace Crystal::Geom;
using namespace Crystal::Physics;

#ifdef _OPENMP
#include <omp.h>
#endif


void SPHSolver::calculateInteraction()
{
	PhysicsObjectVector& objects = factory->getPhysicsObjects();
	ParticleVector particles = factory->getParticles();
	if( particles.empty() ) {
		return;
	}

	for( size_t i = 0; i < particles.size(); ++i ) {
		particles[i]->resetDiffParameters();
	}

	createPairs();
		
	SPHPairSolver solver( setting.getEffectLength() );

	calculateDensity();
	
	Profiler::get()->start(" Sim->force");
	const std::vector<ParticlePair>& pairs = neighborSearcher->getPairs();
	#pragma omp parallel for
	for( int i = 0; i < static_cast<int>(pairs.size()); ++i ) {
		sphPairSolver->calculatePressureForce( pairs[i]);
		sphPairSolver->calculateViscosityForce( pairs[i]);
		sphPairSolver->calculateNormal( pairs[i]);
	}
	Profiler::get()->end(" Sim->force");

	calculateBoundaryForce();
}

void SPHSolver::createPairs()
{
	assert( neighborSearcher == 0 );
	Profiler::get()->start(" Sim->sorting");	
	SearchParticleFactory spFactory( factory->getParticles(), setting.getEffectLength() );
	const SearchParticleVector& sorted = spFactory.getSearchParticles();
	Profiler::get()->end(" Sim->sorting");

	Profiler::get()->start(" Sim->search");
	neighborSearcher = new NeighborSearcher( sorted, setting.getEffectLength() );
	neighborSearcher->search();
	Profiler::get()->end(" Sim->search");
}

void SPHSolver::calculateDensity()
{
	Profiler::get()->start(" Sim->density");
	const std::vector<ParticlePair>& pairs = neighborSearcher->getPairs();

	#pragma omp parallel for
	for( int i = 0; i < (int)(pairs.size()); ++i ) {
		sphPairSolver->calculateBoundaryDensity( pairs[i]);
	}
	const ParticleVector& particles = factory->getParticles();

	for( int i = 0; i < (int)particles.size(); ++i ) {
		sphPairSolver->calculateDensity( particles[i] );
	}
	
	Profiler::get()->end(" Sim->density");
}

void SPHSolver::calculateBoundaryForce()
{
	Profiler::get()->start(" Sim->boundary");
	const PhysicsObjectVector& objects = factory->getPhysicsObjects();
	for( PhysicsObjectVector::const_iterator iter = objects.begin(); iter != objects.end(); ++iter ) {
		BoundarySolver boundarySolver( (*iter), setting );
		boundarySolver.calculateForce( setting.boundaryBox );
	}
	Profiler::get()->end(" Sim->boundary");
}