#ifndef __CRYPHOUS_BOUNDARY_SOLVER_H__
#define __CRYPHOUS_BOUNDARY_SOLVER_H__

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
		setting( setting)
	{}

	~BoundarySolver(void){};

	void calculateForce(const Geometry::Box& box);

private:
	PhysicsObject* object;
	const SimulationSetting& setting;
};

	}
}

#endif