#ifndef __CRYSTAL_PHYSICS_PHYSICS_OBJECT_H__
#define __CRYSTAL_PHYSICS_PHYSICS_OBJECT_H__

#include "Coordinator.h"

namespace Crystal {
	namespace Physics {

class PhysicsObject {
public:
	PhysicsObject( const ParticleVector& particles, const CoordinatorVector& coordinators );

	~PhysicsObject();

	void coordinate( const float timeStep ) const;

	ParticleVector getParticles() const { return particles; }

	void clear();

private:
	ParticleVector particles;
	CoordinatorVector coordinators;
};

class PhysicsObjectCollection {
public:
	void push_back( PhysicsObject* object ) { objects.push_back( object ); }

	void clear();

	ParticleVector getParticles() const;

	void coordinate( const float timeStep ) const;

private:
	std::vector<PhysicsObject*> objects;
};


	}
}

#endif