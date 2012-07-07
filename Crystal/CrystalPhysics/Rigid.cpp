
#include "Rigid.h"
#include "Particle.h"
#include "EnforcerBase.h"

#include <boost/foreach.hpp>

using namespace Crystal::Geom;
using namespace Crystal::Physics;

Rigid::Rigid( const int id, const double density, const double gasConstant, const double viscosityCoefficient, 
			 ParticleFactory* particleFactory,
			 EnforcerBase* enforcerBase ) :
PhysicsObject( id , density, gasConstant, viscosityCoefficient, particleFactory, enforcerBase)
{
}

Rigid::~Rigid()
{
}

void Rigid::integrateTime(const double proceedTime)
{
	const ParticleVector& particles = getParticles();
	BOOST_FOREACH( Particle* particle, particles ) {
		Vector3d accelaration = particle->force / particle->density;
		particle->velocity += (accelaration * proceedTime);
		particle->center += (particle->velocity * proceedTime);
	}
}