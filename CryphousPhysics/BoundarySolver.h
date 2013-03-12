#ifndef __CRYPHOUS_BOUNDARY_SOLVER_H__
#define __CRYPHOUS_BOUNDARY_SOLVER_H__

#include <vector>

namespace Cryphous{
	namespace Geometry{
		class Box;
		class Sphere;
	}
	namespace Physics{

		class PhysicsObject;
		class SimulationSetting;

class BoundarySolver
{
public:

	BoundarySolver(PhysicsObject* object, const SimulationSetting& setting)
		: object( object),
		setting( setting)
	{}

	~BoundarySolver(void){};

	void calculateForce(const Geometry::Box& box);

	void calculateForce(const Geometry::Sphere& box);

private:
	PhysicsObject* object;
	const SimulationSetting& setting;
};

	}
}

#endif