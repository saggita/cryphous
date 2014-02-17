#include "PhysicsObject.h"

using namespace Crystal::Physics;

PhysicsObject::PhysicsObject( const ParticleVector& particles, const CoordinatorVector& coordinators ) :
	particles( particles ),
	coordinators( coordinators )
{
}

PhysicsObject::~PhysicsObject()
{
	clear();
}

void PhysicsObject::coordinate( const float timeStep ) const {
	for( Coordinator* coordinator : coordinators ) {
		coordinator->coordinate( particles, timeStep );
	}
}

void PhysicsObject::clear()
{
	for( Particle* particle : particles ) {
		delete particle;
	}
	for( Coordinator* coordinator : coordinators ) {
		delete coordinator;
	}
	particles.clear();
	coordinators.clear();
}

void PhysicsObjectCollection::clear()
{
	for( PhysicsObject* object : objects ) {
		delete object;
	}
	objects.clear();
}

ParticleVector PhysicsObjectCollection::getParticles() const
{
	ParticleVector ordered;
	for( const PhysicsObject* object : objects ) {
		const ParticleVector& particles = object->getParticles();
		ordered.insert( ordered.end(), particles.begin(), particles.end() );
	}
	return ordered;
}

void PhysicsObjectCollection::coordinate( const float timeStep ) const
{
	for( PhysicsObject* object : objects ) {
		object->coordinate( timeStep );
	}
}