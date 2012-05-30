#ifndef __FLUID_SOLVER_TEST_H_
#define __FLUID_SOLVER_TEST_H_

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