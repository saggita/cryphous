#ifndef __SPH_SOLVER_H__
#define __SPH_SOLVER_H__

#include "NeighborSearcher.h"
#include "SPHPairSolver.h"
#include "PhysicsObjectFactory.h"
#include "SimulationSetting.h"
#include "Profiler.h"
#include "BoundarySolver.h"

#ifdef _OPENMP
#include <omp.h>
#endif

namespace Crystal{
	namespace Physics{

class SPHSolver
{
public:
	SPHSolver(PhysicsObjectFactory* factory, const SimulationSetting& setting) :
	  factory( factory),
		  setting( setting),
		  neighborSearcher( 0),
		  sphPairSolver( new SPHPairSolver( setting.getEffectLength() ) )
	  {
	  }

	~SPHSolver(void)
	{
		delete neighborSearcher;
		delete sphPairSolver;
	}

	void calculateInteraction()
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
		}
		Profiler::get()->end(" Sim->force");

		calculateBoundaryForce();
	}

private:
	void createPairs()
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

	void calculateDensity()
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

	void calculateBoundaryForce()
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

private:
	PhysicsObjectFactory* factory;
	const SimulationSetting& setting;
	NeighborSearcher* neighborSearcher;
	SPHPairSolver* sphPairSolver;
};

	}
}

#endif