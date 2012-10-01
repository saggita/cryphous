#ifndef __BOUNDARY_SOLVER_H__
#define __BOUNDARY_SOLVER_H__

#include "../CrystalGeom/Vector3d.h"
#include "../CrystalGeom/Box.h"
#include "PhysicsObject.h"
#include "ParticlePair.h"
#include "SPHPairSolver.h"
#include "SimulationSetting.h"

#include <vector>



namespace Crystal{
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

	void calculateDensity(const Geom::Box& box);

	void calculateForce(const Geom::Box& box);

private:

	void calculateDensity(Particle* particle, const Geom::Vector3d boundaryPoint);

private:
	PhysicsObject* object;
	Particle* virtualParticle;
	const SimulationSetting& setting;
};

	}
}

#endif