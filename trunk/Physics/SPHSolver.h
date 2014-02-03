#ifndef __CRYSTAL_PHYSICS_SPH_SOLVER_H__
#define __CRYSTAL_PHYSICS_SPH_SOLVER_H__

#include "Particle.h"
#include "PhysicsObject.h"

namespace Crystal{
	namespace Physics{

class SPHSolver
{
public:

	void init();

	void solve( const ParticleVector& particles, const float effectLength );

	void simulate(const PhysicsObjectCollection& objects, const float effectLength, const float timeStep);

	int getStep() const { return step; }

	float getSimulationTime() const { return simulationTime; }

private:
	int step;
	float simulationTime;
};

	}
}

#endif