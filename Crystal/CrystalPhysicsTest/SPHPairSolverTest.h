#ifndef __SPH_PAIR_SOLVER_TEST_H_
#define __SPH_PAIR_SOLVER_TEST_H_

namespace Crystal{
	namespace Physics{
		class PhysicsObjectFactory;
	}
}

class SPHPairSolverTest
{
public:
	SPHPairSolverTest();
	
	~SPHPairSolverTest();

	void calculateDensityTest();

	void calculateBoundaryDensityTest();

	void calculatePressureForceTest();
};

#endif