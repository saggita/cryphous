#ifndef __SPH_SOLVER_H__
#define __SPH_SOLVER_H__

namespace Crystal{
	namespace Physics{
		class NeighborSearcher;
		class SPHPairSolver;
		class PhysicsObjectFactory;
		class SimulationSetting;

class SPHSolver
{
public:
	SPHSolver(PhysicsObjectFactory* factory, const SimulationSetting& setting);

	~SPHSolver(void);

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
};

	}
}

#endif