#ifndef __CRYSTAL_PHYSICS_BOUNDARY_SOLVER_H__
#define __CRYSTAL_PHYSICS_BOUNDARY_SOLVER_H__

#include "Coordinator.h"

#include "../Math/Box.h"

#include <vector>

namespace Crystal{
	namespace Math{
		class Box;
	}
	namespace Physics{

class BoundaryCoordinator : public Coordinator
{
public:
	BoundaryCoordinator(const Math::Box& box) :
		box( box )
	{}

	~BoundaryCoordinator(void){};

	virtual void coordinate(const ParticleVector& particles, const float timeStep);

private:
	const Math::Box box;
};

class SphereBoundaryCoordinator : public Coordinator
{
public:
	SphereBoundaryCoordinator(const float radius, const Math::Vector3d& center) :
		radius( radius ),
		center( center )
	{}

	~SphereBoundaryCoordinator(void){};

	virtual void coordinate(const ParticleVector& particles, const float timeStep);

private:
	const float radius;
	const Math::Vector3d center;
};

	}
}

#endif