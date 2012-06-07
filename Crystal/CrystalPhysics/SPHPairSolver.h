#ifndef __SPH_PAIR_SOLVER_H__
#define __SPH_PAIR_SOLVER_H__

namespace Crystal{

	namespace Geom{
		class Vector3d;
	}

	namespace Physics {

		class Particle;
		class Kernels;
		class ParticlePair;

class SPHPairSolver
{
public:

	SPHPairSolver(const double effectLength );

	~SPHPairSolver();

	void calculateIntermediateDensity( ParticlePair* pair );

	void calculateIntermediateDensity( Particle* particle );

	void calculateDensity( ParticlePair* pair );

	void calculateDensity( Particle* particle );

	void calculateBoundaryDensity( ParticlePair* pair );

	void calculatePressureForce( ParticlePair* pair);

	void calculateSurfaceTension( ParticlePair* pair );

	void calculateViscosityForce( ParticlePair* pair );

private:
	ParticlePair* pair;
	Kernels* kernels;
};

	}
}

#endif