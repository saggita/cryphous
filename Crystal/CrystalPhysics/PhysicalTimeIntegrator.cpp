#include "PhysicalTimeIntegrator.h"

#include "Particle.h"
#include "ParticleDerive.h"
#include "PhysicsObject.h"

#include "../CrystalGeom/Vector3d.h"

#include <boost/foreach.hpp>

using namespace Crystal::Geom;
using namespace Crystal::Physics;

PhysicalTimeIntegrator::PhysicalTimeIntegrator(void)
{
}


PhysicalTimeIntegrator::~PhysicalTimeIntegrator(void)
{
}

void PhysicalTimeIntegrator::integrateTime(const PhysicsObject& object, const double proceedTime )
{
	const ParticleVector& particles = object.getParticles();
	BOOST_FOREACH( Particle* particle, particles ) {
		Vector3d accelaration = particle->getDerive()->force / particle->getDensity();
		particle->velocity += (accelaration * proceedTime);
		particle->center += (particle->velocity * proceedTime);
	}
}