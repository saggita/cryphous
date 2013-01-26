#ifndef __BOUNDARY_SOLVER_H__
#define __BOUNDARY_SOLVER_H__

#include "../CryphousGeometry/Vector3d.h"
#include "../CryphousGeometry/Box.h"
#include "PhysicsObject.h"
#include "ParticlePair.h"
#include "SPHPairSolver.h"
#include "SimulationSetting.h"

#include <vector>



namespace Cryphous{
	namespace Physics{

class BoundarySolver
{
public:

	BoundarySolver(PhysicsObject* object, const SimulationSetting& setting)
		: object( object),
		virtualParticle( object->getParticleFactory()->getVirtualParticle()),
		setting( setting)
	{}

	~BoundarySolver(void){};

	void calculateDensity(const Geometry::Box& box);

	void calculateForce(const Geometry::Box& box);

private:

	void calculateDensity(Particle* particle, const Geometry::Vector3d boundaryPoint);

private:
	PhysicsObject* object;
	Particle* virtualParticle;
	const SimulationSetting& setting;
};

	}
}

#endif