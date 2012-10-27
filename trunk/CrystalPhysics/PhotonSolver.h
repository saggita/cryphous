#ifndef __PHOTON_SOLVER_H__
#define __PHOTON_SOLVER_H__

#include "SearchParticleFactory.h"

namespace Crystal{
	namespace Physics{
		class SimulationSetting;
		class NeighborPhotonSearcher;
		class LightSourceFactory;
		class SearchParticle;
		typedef std::vector<SearchParticle> SearchParticleVector;
		class SearchPhoton;
		typedef std::vector<SearchPhoton> SearchPhotonVector;

class PhotonSolver
{
public:
	PhotonSolver(LightSourceFactory* factory, const SimulationSetting& setting) :
	  factory( factory),
		  setting( setting),
		  neighborSearcher( 0)
	  {
	  }

	~PhotonSolver(void);

	void calculateInteraction(const SearchParticleVector& sortedParticles, const SearchPhotonVector& sortedPhotons);
		
	void calculateBoundaryIntersection();

private:
	void createPairs(const SearchParticleVector& sortedParticles, const SearchPhotonVector& sortedPhotons);

	void calculateParticlePhotonIntersection();



private:
	LightSourceFactory* factory;
	const SimulationSetting& setting;
	NeighborPhotonSearcher* neighborSearcher;
};

	}
}

#endif