#ifndef __SPH_SOLVER_H__
#define __SPH_SOLVER_H__

namespace Crystal{
	namespace Physics{
		class NeighborSearcher;
		class SPHPairSolver;
		class PhysicsObjectFactory;

class SPHSolver
{
public:
	SPHSolver(PhysicsObjectFactory* factory, const double effectLength);

	~SPHSolver(void);

	void calculateInteraction();

private:
	void createPairs();

	void calculateDensity();

	void calculateBoundaryForce();

	double getEffectLength() { return effectLength; }

private:
	PhysicsObjectFactory* factory;
	const double effectLength;
	NeighborSearcher* neighborSearcher;
	SPHPairSolver* sphPairSolver;
};

	}
}

#endif