#ifndef __SPH_SOLVER_H__
#define __SPH_SOLVER_H__

#include "NeighborSearcher.h"
#include "SPHPairSolver.h"
#include "PhysicsObjectFactory.h"
#include "SimulationSetting.h"
#include "Profiler.h"
#include "BoundarySolver.h"
#include "SearchParticleFactory.h"


namespace Cryphous{
	namespace Physics{

class SPHSolver
{
public:
	SPHSolver(PhysicsObjectFactory* factory, const SimulationSetting& setting, const SearchParticleVector& sortedParticles) :
	  factory( factory),
		  setting( setting),
		  neighborSearcher( 0),
		  sphPairSolver( new SPHPairSolver( setting.getEffectLength() ) ),
		  sortedParticles( sortedParticles)
	  {
	  }

	~SPHSolver(void)
	{
		delete neighborSearcher;
		delete sphPairSolver;
	}

	void calculateInteraction();

private:
	void createPairs();

	void calculateDensity();

	void calculateBoundaryForce();

private:
	PhysicsObjectFactory* factory;
	const SimulationSetting& setting;
	NeighborSearcher* neighborSearcher;
	SPHPairSolver* sphPairSolver;
	const SearchParticleVector& sortedParticles;
};

	}
}

#endif