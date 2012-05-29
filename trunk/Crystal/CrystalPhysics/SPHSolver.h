#ifndef __SPH_SOLVER_H__
#define __SPH_SOLVER_H__

namespace Crystal{
	namespace Physics{
		class NeighborSearcher;
		class SPHPairSolver;

class SPHSolver
{
public:
	SPHSolver(const double effectLength);

	~SPHSolver(void);

	void calculateInteraction();

private:
	void createPairs();

	void calculateDensity();

	void calculateBoundaryForce();

	void calculatePressureForce();
		
	void calculateViscosityForce();

	void calculateColorFlameGradient();

	double getEffectLength() { return effectLength; }

private:
	const double effectLength;
	NeighborSearcher* neighborSearcher;
	SPHPairSolver* sphPairSolver;
};

	}
}

#endif