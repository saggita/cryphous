#include "Elastic.h"

using namespace Cryphous::Geometry;
using namespace Cryphous::Physics;

void Elastic:: integrateTime(const float proceedTime)
{
	const ParticleVector& particles = getParticles();
	if( !particles.empty() ) {
		particles.front()->force = Geometry::Vector3d(0.0f, 0.0f, 0.0f);
	}

	for( Particle* particle: particles ) {
		Geometry::Vector3d accelaration = particle->force / particle->density;
		particle->velocity += (accelaration * proceedTime);
		particle->center += (particle->velocity * proceedTime);
	}
}

void Elastic::enforce(const float proceedTime)
{
	const ParticleVector& particles = getParticles();
	if( particles.empty() ){
		return;
	}
	for( size_t i = 0; i < particles.size() -1; ++i ) {
		Particle* particleX = particles[i];
		Particle* particleY = particles[i+1];
		Geometry::Vector3d distanceVector = particleX->center - particleY->center;
		const float distance = distanceVector.getLength();
		particleX->force -= getGasConstant() * 10.0f * ( distance - particleX->getDiameter()) * distanceVector / distance;
		particleY->force += getGasConstant() * 10.0f * ( distance - particleY->getDiameter()) * distanceVector / distance;
		particleX->force -= getViscosityCoefficient() * 1.0f * ( particleX->velocity - particleY->velocity );
		particleY->force += getViscosityCoefficient() * 1.0f * ( particleX->velocity - particleY->velocity );
	}
}