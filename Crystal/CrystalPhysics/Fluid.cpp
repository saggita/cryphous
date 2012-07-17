#include "Fluid.h"

#include "Particle.h"

#include "../CrystalGeom/Vector3d.h"
#include "../CrystalGeom/Vector3d.h"

#include <boost/foreach.hpp>

using namespace Crystal::Geom;
using namespace Crystal::Physics;


Fluid::Fluid(const int id, const float density, const float gasConstant, const float viscosityCoefficient, ParticleFactory* particleFactory) :
PhysicsObject( id, density, gasConstant, viscosityCoefficient,particleFactory )
{
}

Fluid::~Fluid(void)
{
}

void Fluid::integrateTime(const float proceedTime)
{
	const ParticleVector& particles = getParticles();
	BOOST_FOREACH( Particle* particle, particles ) {
		Vector3d accelaration = particle->force / particle->density;
		particle->velocity += (accelaration * proceedTime);
		particle->center += (particle->velocity * proceedTime);
	}
}