
#include "SPHSolver.h"

#include "PhysicsObjectFactory.h"
#include "PhysicsObject.h"

#include "ParticleDerive.h"
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
#include "SPHPairSolver.h"
#include "PhysicsObject.h"
#include "SimulationSetting.h"
#include "ParticleDerive.h"
#include "../CrystalGeom/Box.h"

#include <cassert>


using namespace Crystal::Physics;
using namespace Crystal::Geom;

SPHSolver::SPHSolver(const double effectLength) :
effectLength( effectLength),
neighborSearcher( 0),
sphPairSolver( new SPHPairSolver( effectLength ) )
{
}

SPHSolver::~SPHSolver()
{
	delete neighborSearcher;
	delete sphPairSolver;
}

void SPHSolver::calculateInteraction()
{
	PhysicsObjectFactory* factory = PhysicsObjectFactory::get();

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
		
	SPHPairSolver solver( effectLength );

	calculateDensity();

	Profiler::get()->start(" Sim->interaction");
	calculatePressureForce();
	calculateViscosityForce();
	Profiler::get()->end(" Sim->interaction");

	calculateBoundaryForce();
}


void SPHSolver::createPairs()
{
	assert( neighborSearcher == 0 );
	Profiler::get()->start(" Sim->sorting");
	const SearchParticleVector& sorted = PhysicsObjectFactory::get()->getSearchParticles(effectLength);
	Profiler::get()->end(" Sim->sorting");

	Profiler::get()->start(" Sim->search");
	neighborSearcher = new NeighborSearcher( sorted, effectLength );
	neighborSearcher->search();
	Profiler::get()->end(" Sim->search");
}

void SPHSolver::calculateDensity()
{
	std::vector<ParticlePair*> pairs = neighborSearcher->getPairs();
	BOOST_FOREACH( ParticlePair* pair, pairs) {
		sphPairSolver->calculateBoundaryDensity( pair);
	}
	const ParticleVector& particles = PhysicsObjectFactory::get()->getSortedParticles();

	BOOST_FOREACH( Particle* particle, particles ) {
		sphPairSolver->calculateDensity( particle );
	}

	//Profiler::get()->end("density");
}

void SPHSolver::calculateBoundaryForce()
{
	Profiler::get()->start(" Sim->boundary");
	const PhysicsObjectList& objects = PhysicsObjectFactory::get()->getPhysicsObjects();
	BOOST_FOREACH( PhysicsObject* object, objects ) {
		const ParticleVector& particles = object->getParticles();
		Particle* virtualParticle = object->getParticleFactory()->getVirtualParticle();
		
		BoundarySolver boundarySolver( object, effectLength );
		boundarySolver.calculateForce( SimulationSetting::get()->boundaryBox );
	}
	Profiler::get()->end(" Sim->boundary");
}

void SPHSolver::calculatePressureForce()
{
	std::vector<ParticlePair*> pairs = neighborSearcher->getPairs();
	#pragma omp parallel for
	//BOOST_FOREACH( ParticlePair* pair, pairs ) {
	for( int i = 0; i < (int)(pairs.size()); ++i ) {
		sphPairSolver->calculatePressureForce( pairs[i]);
	}
}
		
void SPHSolver::calculateViscosityForce()
{
	std::vector<ParticlePair*> pairs = neighborSearcher->getPairs();
	#pragma omp parallel for
	//BOOST_FOREACH( ParticlePair* pair, pairs ) {
	for( int i = 0; i < (int)(pairs.size()); ++i ) {
		sphPairSolver->calculateViscosityForce( pairs[i]);
	}
}