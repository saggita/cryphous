
#include "SPHSolver.h"

#include "PhysicsObjectFactory.h"
#include "PhysicsObject.h"

#include "ParticleFactory.h"
#include "ParticlePair.h"
#include "SPHPairSolver.h"
#include "Simulation.h"

#include "SimulationSetting.h"

#include "Profiler.h"

#include "SearchParticle.h"
#include "SearchParticleFactory.h"

#include <boost/foreach.hpp>

#ifdef _OPENMP
#include <omp.h>
#endif


#include "ParticlePair.h"
#include "Profiler.h"
#include "PhysicsObjectFactory.h"
#include "BoundarySolver.h"
#include "NeighborSearcher.h"
#include "../CrystalGeom/Box.h"

#include <cassert>


using namespace Crystal::Physics;
using namespace Crystal::Geom;

SPHSolver::SPHSolver(PhysicsObjectFactory* factory, const SimulationSetting& setting) :
factory( factory),
setting( setting),
neighborSearcher( 0),
sphPairSolver( new SPHPairSolver( setting.getEffectLength() ) )
{
}

SPHSolver::~SPHSolver()
{
	delete neighborSearcher;
	delete sphPairSolver;
}

void SPHSolver::calculateInteraction()
{
	PhysicsObjectList& objects = factory->getPhysicsObjects();
	ParticleVector particles = factory->getSortedParticles();
	if( particles.empty() ) {
		return;
	}

	BOOST_FOREACH( Particle *particle, particles ) {
		particle->resetDiffParameters();
	}

	particles = factory->getSortedParticles();

	if( particles.empty() ) {
		return;
	}

	createPairs();
		
	SPHPairSolver solver( setting.getEffectLength() );

	calculateDensity();

	Profiler::get()->start(" Sim->force");
	const std::vector<ParticlePair>& pairs = neighborSearcher->getPairs();
	#pragma omp parallel for
	for( int i = 0; i < (int)(pairs.size()); ++i ) {
		sphPairSolver->calculatePressureForce( pairs[i]);
		sphPairSolver->calculateViscosityForce( pairs[i]);
		sphPairSolver->calculateNormal( pairs[i]);
		sphPairSolver->countNeighbors( pairs[i]);
	}
	Profiler::get()->end(" Sim->force");

	calculateBoundaryForce();
}


void SPHSolver::createPairs()
{
	assert( neighborSearcher == 0 );
	Profiler::get()->start(" Sim->sorting");
	const SearchParticleVector& sorted = factory->getSearchParticles( setting.getEffectLength() );
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
	const ParticleVector& particles = factory->getSortedParticles();

	for( int i = 0; i < (int)particles.size(); ++i ) {
		sphPairSolver->calculateDensity( particles[i] );
	}
	
	Profiler::get()->end(" Sim->density");
}

void SPHSolver::calculateBoundaryForce()
{
	Profiler::get()->start(" Sim->boundary");
	const PhysicsObjectList& objects = factory->getPhysicsObjects();
	BOOST_FOREACH( PhysicsObject* object, objects ) {
		const ParticleVector& particles = object->getParticles();
		Particle* virtualParticle = object->getParticleFactory()->getVirtualParticle();
		
		BoundarySolver boundarySolver( object, setting );
		boundarySolver.calculateForce( setting.boundaryBox );
	}
	Profiler::get()->end(" Sim->boundary");
}