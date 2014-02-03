#include "Coordinator.h"

#include "../Math/Vector3d.h"

#include "Particle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

void StaticIntegrator::coordinate(const ParticleVector& particles, const float proceedTime)
{
	;
}

void EulerIntegrator::coordinate(const ParticleVector& particles, const float proceedTime)
{
	for( Particle* particle : particles ) {
		Vector3d accelaration = particle->getAccelaration();//particle->variable.force / particle->variable.density;
		particle->addVelocity( accelaration * proceedTime );
		particle->addCenter( particle->getVelocity() * proceedTime);
	}
}

void ExternalForceCoordinator::coordinate(const ParticleVector& particles, const float timeStep)
{
	for( Particle* particle: particles ) {
		particle->addForce( force * particle->getDensity() );
	}
}