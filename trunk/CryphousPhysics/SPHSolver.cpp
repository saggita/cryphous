#include "SPHSolver.h"

#include "SphereBoundarySolver.h"

using namespace Cryphous::Geometry;
using namespace Cryphous::Physics;

#ifdef _OPENMP
#include <omp.h>
#endif


void SPHSolver::calculateInteraction()
{
	PhysicsObjectVector& objects = factory->getPhysicsObjects();
	ParticleVector particles = factory->getParticles();
	if( particles.empty() ) { return; }

	for( Particle* particle : particles ) { particle->resetDiffParameters(); }

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
	Profiler::get()->start(" Sim->search");
	neighborSearcher = new NeighborSearcher( sortedParticles, setting.getEffectLength() );
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
		//BoundarySolver boundarySolver( (*iter), setting );
		//boundarySolver.calculateForce( setting.boundaryBox );
		SphereBoundarySolver bs( *iter, setting );
		Sphere sphere( Vector3d( 0.0, 0.0, 0.0), 30.0f );
		bs.calculateForce( sphere );
	}
	Profiler::get()->end(" Sim->boundary");
}