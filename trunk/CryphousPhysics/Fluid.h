#ifndef __FLUID_H__
#define __FLUID_H__

#include "../CryphousGeometry/Vector3d.h"

#include "PhysicsObject.h"
#include "Particle.h"

namespace Cryphous{
	namespace Physics{

class Fluid : public PhysicsObject
{
public:
	Fluid(const int id, const float density, const float gasConstant, const float viscosityCoefficient,ParticleFactory* particleFactory) :
	  PhysicsObject( id, density, gasConstant, viscosityCoefficient,particleFactory )
	  {
	  }

	virtual ~Fluid(void){};

	virtual Type getType() { return PhysicsObject::Fluid; }

	virtual void integrateTime(const float proceedTime) {
		const ParticleVector& particles = getParticles();
		for( ParticleVector::const_iterator iter = particles.begin(); iter != particles.end(); ++iter ) {
			Particle* particle = *iter;
			Geometry::Vector3d accelaration = particle->force / particle->density;
			particle->velocity += (accelaration * proceedTime);
			particle->center += (particle->velocity * proceedTime);
		}
	}

	virtual void enforce(const float proceedTime){};
};
	}
}

#endif