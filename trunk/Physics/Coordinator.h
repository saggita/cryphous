#ifndef __CRYSTAL_PHYSICS_COORDINATOR_H__
#define __CRYSTAL_PHYSICS_COORDINATOR_H__

#include <vector>

#include "Particle.h"

#include "../Math/Vector3d.h"

namespace Crystal{
	namespace Physics{

class Coordinator
{
public:
	virtual ~Coordinator(){}

	virtual void coordinate( const ParticleVector& particles, const float timeStep ) = 0;
};

typedef std::vector<Coordinator*> CoordinatorVector;

class StaticIntegrator : public Coordinator
{
public:
	void coordinate( const ParticleVector& particles, const float timeStep );
};

class EulerIntegrator : public Coordinator
{
public:
	void coordinate( const ParticleVector& particles, const float timeStep );
};


class ExternalForceCoordinator : public Coordinator
{
public:
	ExternalForceCoordinator(const Math::Vector3d& force) :
		force( force )
	{}

	void coordinate( const ParticleVector& particles, const float timeStep );

private:
	Math::Vector3d force;
};

	}
}

#endif